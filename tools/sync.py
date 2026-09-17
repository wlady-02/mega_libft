#!/usr/bin/env python3
"""Tiene allineata la documentazione di mega_libft.

La fonte unica e' mega_libft.h: ogni prototipo ha sopra di se' il suo blocco
/** ... */ in formato Doxygen. Questo script copia quei blocchi sopra le
implementazioni corrispondenti sotto src/ e in mega_libft.c, e rigenera le due
versioni monofile sotto single/.

Se cambi la descrizione di una funzione, cambiala nell'header e lancia lo
script: tutto il resto si adegua.

Le funzioni che nell'header non compaiono (le static di servizio, e le tre
funzioni interne di get_next_line) restano documentate nel loro .c, dove sono
l'unica copia: lo script non le tocca.

Uso:
    python3 tools/sync.py            allinea .c e single/
    python3 tools/sync.py --check    verifica soltanto, esce con 1 se
                                    disallineato

oppure, dal Makefile:  make sync   /   make sync-check
"""

import os
import re
import subprocess
import sys

HEADER = 'mega_libft.h'
SINGLE = [('BASE_SRCS', 'single/mega_libft.c', False),
          ('BONUS_SRCS', 'single/mega_libft_bonus.c', True)]

NAME = re.compile(r'\b(\w+)\s*\(')
DEF = re.compile(r'^(?:static\s+)?[A-Za-z_][^\n;{]*\([^;{]*\)\s*$')
BANNER_LINE = re.compile(r'^/\*.*\*/$')


def read(path):
    with open(path) as fp:
        return fp.read()


def write(path, text):
    with open(path, 'w') as fp:
        fp.write(text)


# --------------------------------------------------------------------------- #
#  lettura della fonte unica
# --------------------------------------------------------------------------- #

def parse_header(text):
    """Ricava dall'header la mappa nome funzione -> blocco di documentazione."""
    lines = text.split('\n')
    docs = {}
    i = 0
    while i < len(lines):
        if lines[i] != '/**':
            i += 1
            continue
        end = i
        while end < len(lines) and lines[end] != ' */':
            end += 1
        if end == len(lines):
            sys.exit('%s: blocco /** aperto alla riga %d e mai chiuso'
                     % (HEADER, i + 1))
        decl, j = '', end + 1
        while j < len(lines) and ';' not in decl:
            decl += lines[j]
            j += 1
        match = NAME.search(decl)
        if match:
            docs[match.group(1)] = '\n'.join(lines[i:end + 1])
        i = end + 1
    return docs


def undocumented(text, docs):
    """Prototipi dell'header rimasti senza blocco di documentazione."""
    missing = []
    for line in text.split('\n'):
        if not line.endswith(';') or line.startswith((' ', '\t', '#', '/')):
            continue
        match = NAME.search(line)
        if match and match.group(1) not in docs:
            missing.append(match.group(1))
    return missing


# --------------------------------------------------------------------------- #
#  propagazione nei .c
# --------------------------------------------------------------------------- #

def sync_source(text, docs):
    """Riscrive i blocchi sopra le definizioni con quelli dell'header."""
    lines = text.split('\n')
    out, i = [], 0
    while i < len(lines):
        line = lines[i]
        if not (DEF.match(line) and i + 1 < len(lines)
                and lines[i + 1] == '{'):
            out.append(line)
            i += 1
            continue
        match = NAME.search(line)
        name = match.group(1) if match else None
        if name in docs:
            while out and out[-1] == ' */':
                start = len(out) - 1
                while start > 0 and out[start] != '/**':
                    start -= 1
                del out[start:]
                while out and out[-1] == '':
                    out.pop()
                out.append('')
            out.extend(docs[name].split('\n'))
        out.append(line)
        i += 1
    return '\n'.join(out)


# --------------------------------------------------------------------------- #
#  rigenerazione delle versioni monofile
# --------------------------------------------------------------------------- #

def make_var(name):
    """Legge una lista di sorgenti dal Makefile, per non duplicarla qui."""
    out = subprocess.run(['make', '-s', 'print-' + name],
                         capture_output=True, text=True, check=True)
    return out.stdout.split()


def strip_source(path, sources):
    """Corpo di un .c senza intestazione 42 e senza include locali.

    Legge da `sources`, cioe' dal testo gia' riallineato in questa passata, non
    dal file su disco: altrimenti un monofile rigenerato nella stessa corsa si
    porterebbe dietro la documentazione vecchia.
    """
    lines = sources[path].split('\n')
    i = 0
    while i < len(lines) and BANNER_LINE.match(lines[i]):
        i += 1
    body = [l for l in lines[i:]
            if not re.match(r'^#[ \t]*include[ \t]*"', l)]
    while body and body[0] == '':
        body.pop(0)
    while body and body[-1] == '':
        body.pop()
    return '\n'.join(body)


def declarations(text, bonus):
    """Contenuto dell'header senza le guardie, da incollare nel monofile."""
    lines = text.split('\n')
    lines = lines[lines.index('# define MEGA_LIBFT_H') + 1:]
    while lines and lines[-1] == '':
        lines.pop()
    if lines[-1] != '#endif':
        sys.exit('%s: l\'ultima riga dovrebbe essere #endif' % HEADER)
    lines.pop()
    if not bonus:
        start = next(i for i, l in enumerate(lines) if 'BONUS - inizio' in l)
        end = next(i for i, l in enumerate(lines) if 'BONUS - fine' in l)
        del lines[start:end + 1]
    lines = [re.sub(r'^# ', '#', l) for l in lines]
    while lines and lines[0] == '':
        lines.pop(0)
    while lines and lines[-1] == '':
        lines.pop()
    return '\n'.join(lines)


def banner(name, header_text):
    """Intestazione 42 del monofile, ricalcata su quella dell'header."""
    lines = header_text.split('\n')
    end = 0
    while BANNER_LINE.match(lines[end]):
        end += 1
    out = list(lines[:end])
    for i, line in enumerate(out):
        if re.match(r'^/\*   \S+\.h ', line):
            out[i] = '/*   %-51s%s   */' % (name, ':+:      :+:    :+:')
    return '\n'.join(out)


def build_single(header_text, srcs, bonus, name, sources):
    note = [
        '/*',
        '** mega_libft in un solo file C: libft + ft_printf + get_next_line.',
        '** Nessun header esterno: include di sistema, t_list, prototipi e',
        '** implementazioni stanno tutti qui.',
        '**',
        '** File generato da tools/sync.py: le modifiche vanno fatte nei',
        '** moduli sotto src/ e nell\'header, poi si rilancia `make sync`.',
        '**',
        '** Uso:  #include "%s"  in cima al tuo main.c, oppure' % name,
        '**       cc -Wall -Wextra -Werror main.c %s' % name,
        '**       dichiarando nel main i prototipi che ti servono.',
        '*/',
    ]
    parts = [banner(name, header_text), '', '\n'.join(note), '',
             declarations(header_text, bonus)]
    for src in srcs:
        parts += ['', '/* ----- %s ----- */' % src, '',
                  strip_source(src, sources)]
    return '\n'.join(parts).rstrip('\n') + '\n'


# --------------------------------------------------------------------------- #

def main():
    check = '--check' in sys.argv[1:]
    here = os.path.dirname(os.path.abspath(__file__))
    os.chdir(os.path.join(here, os.pardir))
    header_text = read(HEADER)
    docs = parse_header(header_text)
    missing = undocumented(header_text, docs)
    if missing:
        print('attenzione, prototipi senza documentazione: %s'
              % ', '.join(missing))

    sources = {}
    for src in sorted(set(make_var('BASE_SRCS')) | set(make_var('BONUS_SRCS'))):
        sources[src] = sync_source(read(src), docs)
    wanted = dict(sources)
    for var, out, bonus in SINGLE:
        wanted[out] = build_single(header_text, make_var(var), bonus,
                                   os.path.basename(out), sources)

    stale = [p for p, text in wanted.items() if read(p) != text]
    if check:
        for path in stale:
            print('disallineato: %s' % path)
        print('%d file da riallineare' % len(stale) if stale
              else 'tutto allineato con %s' % HEADER)
        return 1 if stale else 0
    for path in stale:
        write(path, wanted[path])
        print('riallineato %s' % path)
    print('%d file aggiornati, %d funzioni documentate nell\'header'
          % (len(stale), len(docs)))
    return 0


if __name__ == '__main__':
    sys.exit(main())
