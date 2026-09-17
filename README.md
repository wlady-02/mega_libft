# mega_libft

La mia libreria C personale: `libft`, `ft_printf` e `get_next_line` messi
insieme in una cosa sola, da portarsi dietro nei progetti.

> **Non e' un progetto della 42.** Ne' della 42 Firenze, ne' della 42 in
> generale. Non ha un subject, non viene valutato, non c'e' una consegna.
> I tre progetti di partenza sono miei lavori della scuola; questo e' quello
> che ci ho costruito sopra per conto mio, perche' avere tre `libft.a` diverse
> da linkare ogni volta era scomodo.
>
> **Il codice delle funzioni e' mio, l'unificazione l'ha fatta
> [Claude](https://claude.ai/code).** Dettagli in [Da dove
> viene](#da-dove-viene).

---

## Configurazione rapida

```sh
git clone https://github.com/wlady-02/mega_libft
cd mega_libft
make
```

Ottieni `libmegaft.a`. Nel tuo codice:

```c
#include "mega_libft.h"

int	main(void)
{
	char	*s;

	s = ft_strtrim("  ciao  ", " ");
	ft_printf("[%s] lunga %d\n", s, (int)ft_strlen(s));
	free(s);
	return (0);
}
```

```sh
cc main.c libmegaft.a -I /percorso/di/mega_libft
```

Dentro hai tutta libft, `ft_printf` e `get_next_line`.

Due varianti:

- `make bonus` al posto di `make` aggiunge anche le liste concatenate
  `ft_lst*`.
- `single/mega_libft.c` e' tutto il progetto in un file solo, senza header
  esterni. Lo copi accanto al tuo `main.c`, ci metti `#include
  "mega_libft.c"` in cima e compili, niente altro da portarsi dietro.

---

## Cosa c'e' dentro

| | |
| --- | --- |
| **libft** | le funzioni di base: stringhe, memoria, conversioni, `ft_split`, `ft_itoa`... |
| **libft bonus** | le liste concatenate `ft_lst*`, solo con `make bonus` |
| **ft_printf** | `ft_printf` con `%c %s %p %d %i %u %x %X %%` |
| **get_next_line** | legge un file una riga per volta, anche piu' file insieme |
| **collegamento** | tre funzioni `ft_mega_*` che fanno parlare i moduli fra loro |

Tutte le funzioni hanno la documentazione nell'header, quindi l'editor ti
mostra descrizione, parametri e valore di ritorno quando ci passi sopra il
mouse.

---

## Da dove viene

I tre progetti di partenza, scritti da me alla 42 Firenze e valutati li':

| progetto | consegnato | voto | repository |
| --- | --- | --- | --- |
| libft | base + bonus | **125/100** | https://github.com/wlady-02/libft |
| ft_printf | base | **100/100** | https://github.com/wlady-02/ft_printf |
| get_next_line | base + bonus | **125/100** | https://github.com/wlady-02/get_next_line |

125 e' il massimo ottenibile: 100 per la parte base piu' 25 per il bonus.

Di ft_printf ho consegnato solo la parte base, e il bonus di quel progetto
sono proprio flag, ampiezza e precisione: e' per questo che `ft_printf` qui
gestisce le conversioni ma non `%-10s` o `%05d`.

Il loro codice qui dentro e' rimasto quello che era. L'unica eccezione e'
`ft_strlen`, che esisteva in tre versioni con firme incompatibili ed e' stata
unificata: com'e' andata sta nella [parte tecnica](#ft_strlen).

**L'unificazione l'ha fatta [Claude](https://claude.ai/code)**: struttura a
moduli, Makefile, header unico, risoluzione dei nomi in conflitto, commenti di
documentazione, versioni monofile e script di allineamento. Le uniche funzioni
non mie sono le tre `ft_mega_*` che collegano i moduli fra loro.

---
---

# Parte tecnica

## Struttura

```
mega_libft/
├── Makefile
├── mega_libft.h                 header unico pubblico e fonte della doc
├── mega_libft.c                 collegamento fra i moduli
├── src/
│   ├── libft/                   modulo 1 - base
│   ├── libft_bonus/             modulo 1 - bonus (ft_lst*)
│   ├── ft_printf/               modulo 2
│   └── get_next_line/           modulo 3
├── single/
│   ├── mega_libft.c             tutto il progetto in un file, base
│   └── mega_libft_bonus.c       tutto il progetto in un file, bonus
└── tools/
    └── sync.py                  allinea la documentazione e i monofile
```

## Makefile

```sh
make            # libmegaft.a in modo BASE
make bonus      # libmegaft.a in modo BONUS
make sync       # riallinea documentazione e monofile
make sync-check # verifica soltanto, esce con 1 se qualcosa e' disallineato
make clean      # rimuove gli oggetti
make fclean     # rimuove anche l'archivio
make re
```

L'unica differenza fra i due modi sono le funzioni di lista di libft:

|                          | `make` | `make bonus` |
| ------------------------ | ------ | ------------ |
| libft base               | si'    | si'          |
| libft bonus (`ft_lst*`)  | no     | si'          |
| ft_printf                | si'    | si'          |
| get_next_line            | si'    | si'          |

I due modi producono lo stesso archivio con contenuti diversi, quindi il
Makefile tiene un marcatore di modo e ricostruisce da solo quando si passa da
`make` a `make bonus` e viceversa.

`BUFFER_SIZE` vale 3 come nell'originale e si cambia con
`make CFLAGS="-Wall -Wextra -Werror -D BUFFER_SIZE=42"`.

## Conflitti fra i moduli

I tre progetti di partenza avevano funzioni con lo stesso nome. La regola
applicata e' `libft` -> `ft_printf` -> `get_next_line`, vince l'ultimo.

| funzione     | vince           | perche'                                                                |
| ------------ | --------------- | ---------------------------------------------------------------------- |
| `ft_calloc`  | get_next_line   | stessa firma di libft, si sostituisce senza attriti                     |
| `ft_strchr`  | get_next_line   | stessa firma di libft, in piu' e' NULL-safe                             |
| `ft_strjoin` | get_next_line   | `char *` invece di `char const *`; nessuna funzione di libft la chiama   |
| `ft_bzero`   | libft           | ft_printf la dichiara soltanto, non la implementa                       |
| `ft_strlen`  | unificata       | vedi sotto                                                              |

### `ft_strlen`

Delle tre versioni, quella di ft_printf era **byte per byte identica** a quella
di libft: duplicato, eliminato. Le altre due erano davvero diverse:

- libft: `size_t ft_strlen(const char *s)` — firma compatibile con tutto il
  resto della libreria, ma va in crash se `s` e' NULL;
- get_next_line: `int ft_strlen(char *str)` — regge il NULL, ma la firma rompe
  la compilazione con `-Werror` di sette funzioni di libft che le passano un
  `const char *`, e `ft_substr` confronterebbe `unsigned int` con `int`.

La versione unica prende il meglio delle due: la firma di libft e la
NULL-safety di get_next_line.

```c
size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s && s[i] != '\0')
		i++;
	return (i);
}
```

`ft_strjoin` di get_next_line resta NULL-safe perche' ora lo e' anche
`ft_strlen`. Come effetto collaterale `ft_putstr_fd(NULL, 1)` non va piu' in
crash.

## get_next_line

Delle due versioni originali e' rimasta solo quella multi file descriptor, che
e' un superset dell'altra. Conserva quello che ha letto oltre la riga
restituita in un array statico indicizzato dal descrittore:

```c
static char	*fcontent[4096];
```

Ogni descrittore ha quindi il suo segnaposto e piu' file possono essere letti
contemporaneamente senza che le letture si mescolino. Il file deve essere
aperto con un fd minore di 4096.

## Documentazione: una sola fonte

Il commento Doxygen di ogni funzione pubblica si scrive in **`mega_libft.h`**,
sopra il suo prototipo. E' l'header che l'editor legge per mostrare la
documentazione quando passi il mouse su una chiamata, quindi deve stare li'.

La stessa documentazione serve pero' anche sopra l'implementazione nel `.c` e
dentro le due versioni monofile, dove l'header non c'e'. Per non copiarla a
mano in tre posti ci pensa `tools/sync.py`:

```sh
make sync         # copia i blocchi dall'header nei .c e rigenera single/
make sync-check   # non scrive niente, esce con 1 se qualcosa e' disallineato
```

Per cambiare una descrizione: la modifichi nell'header, lanci `make sync`, e i
`.c` e i due file sotto `single/` si adeguano da soli. `make sync-check` e' la
versione in sola lettura, buona come controllo prima di un commit o dentro una
CI.

Due cose che lo script **non** tocca:

- le funzioni `static` di servizio e le tre funzioni interne di get_next_line,
  che nell'header non compaiono: li' il `.c` e' l'unica copia e resta com'e';
- il codice. Sposta soltanto blocchi di commento e riscrive `single/`.

Se aggiungi un prototipo all'header senza documentarlo, te lo dice:

```
attenzione, prototipi senza documentazione: ft_lstsize
```

## Versione monofile

`single/mega_libft.c` e `single/mega_libft_bonus.c` contengono tutto: include
di sistema, `t_list`, prototipi e implementazioni. Nessun `.h` esterno.

```sh
cc -Wall -Wextra -Werror main.c single/mega_libft.c
```
dichiarando nel `main` i prototipi che ti servono, oppure piu' semplicemente
`#include "mega_libft.c"` in cima al tuo file.

Sono **generati** da `make sync`: non vanno modificati a mano.

## Norminette

Questo progetto sta fuori dalla 42, quindi la norminette non e' un vincolo:
nessuno lo valuta. I commenti li ho scritti in formato Doxygen guardando a come
li legge l'editor, non a cosa dice la norma.

Detto questo, com'e' venuta la norma la passa quasi tutta: `norminette` non
segnala niente su `mega_libft.c` e su tutti i 49 file sotto `src/`, blocchi di
documentazione compresi. Restano fuori due cose, per scelta:

- **tre dichiarazioni in `mega_libft.h`.** `const char *ft_mega_version(void)`
  ha un tipo di ritorno lungo dieci caratteri, che non entra nel campo di
  allineamento a otto colonne usato dal resto dell'header. Per farcelo entrare
  dovrei togliere il `const`, e restituire un letterale come `char *` mi sembra
  peggio di tre errori di allineamento.
- **i due file sotto `single/`.** Sono l'intero progetto in un file solo: la
  regola di una funzione per file e il divieto di `typedef` fuori da un header
  non hanno senso li'.

## Funzioni aggiunte

Le uniche funzioni scritte da zero per questo progetto stanno in
`mega_libft.c`, e servono solo a collegare i moduli fra loro:

```c
const char	*ft_mega_version(void);
int			ft_mega_print_next_line(int fd);   /* get_next_line -> ft_printf */
int			ft_mega_print_file(int fd);        /* stampa tutto il file        */
```

Tutto il resto e' il codice originale dei tre progetti, con l'unica eccezione
di `ft_strlen` spiegata sopra.
