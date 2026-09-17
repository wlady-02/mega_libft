/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mega_libft_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwilun <dwilun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/16 00:00:00 by dwilun            #+#    #+#             */
/*   Updated: 2026/09/17 16:52:40 by dwilun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** mega_libft in un solo file C: libft + ft_printf + get_next_line.
** Nessun header esterno: include di sistema, t_list, prototipi e
** implementazioni stanno tutti qui.
**
** File generato da tools/sync.py: le modifiche vanno fatte nei
** moduli sotto src/ e nell'header, poi si rilancia `make sync`.
**
** Uso:  #include "mega_libft_bonus.c"  in cima al tuo main.c, oppure
**       cc -Wall -Wextra -Werror main.c mega_libft_bonus.c
**       dichiarando nel main i prototipi che ti servono.
*/

/*
** Header unico di mega_libft: unisce libft, ft_printf e get_next_line.
**
** Gerarchia in caso di funzione presente in piu' moduli:
**     libft  ->  ft_printf  ->  get_next_line   (vince l'ultimo)
**
** Funzioni contese e modulo che le fornisce:
**     ft_calloc   -> get_next_line   (stessa firma di libft)
**     ft_strchr   -> get_next_line   (stessa firma di libft, in piu' e'
**                                     NULL-safe)
**     ft_strjoin  -> get_next_line   (char * invece di char const *)
**     ft_bzero    -> libft           (ft_printf la dichiara soltanto)
**     ft_strlen   -> unificata       (firma di libft, size_t e const char *,
**                                     piu' la NULL-safety di get_next_line)
*/

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 3
#endif

#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <stdarg.h>
#include <stdio.h>
#include <fcntl.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

/* ========================================================================== */
/*                          MODULO 1 - libft (base)                           */
/* ========================================================================== */

/**
 * @brief Dice se un carattere e' una lettera dell'alfabeto.
 *
 * @param c Carattere da esaminare, passato come unsigned char o EOF.
 * @return int 1 se il carattere e' una lettera maiuscola o minuscola, 0
 *         altrimenti.
 */
int		ft_isalpha(int c);

/**
 * @brief Dice se un carattere e' una cifra decimale.
 *
 * @param c Carattere da esaminare, passato come unsigned char o EOF.
 * @return int 1 se il carattere sta fra '0' e '9', 0 altrimenti.
 */
int		ft_isdigit(int c);

/**
 * @brief Dice se un carattere e' una lettera o una cifra.
 *
 * @param c Carattere da esaminare, passato come unsigned char o EOF.
 * @return int 1 se il carattere e' alfanumerico, 0 altrimenti.
 */
int		ft_isalnum(int c);

/**
 * @brief Dice se un carattere appartiene alla tabella ASCII.
 *
 * @param c Intero da esaminare.
 * @return int 1 se il valore sta fra 0 e 127 compresi, 0 altrimenti.
 */
int		ft_isascii(int c);

/**
 * @brief Dice se un carattere e' stampabile, spazio compreso.
 *
 * @param c Carattere da esaminare, passato come unsigned char o EOF.
 * @return int 1 se il valore sta fra 32 e 126 compresi, 0 altrimenti.
 */
int		ft_isprint(int c);

/**
 * @brief Conta i caratteri di una stringa fino al terminatore, escluso.
 *
 * @param s Stringa da misurare. Puo' essere NULL: in quel caso non viene letto
 *        niente.
 * @return size_t La lunghezza di s, 0 se s e' NULL.
 */
size_t	ft_strlen(const char *s);

/**
 * @brief Riempie i primi n byte di un'area di memoria con un byte dato.
 *
 * @param s Area da riempire. Non puo' essere NULL e deve essere grande almeno n
 *        byte.
 * @param c Valore da scrivere, ridotto a unsigned char.
 * @param n Numero di byte da riempire.
 * @return void * s.
 */
void	*ft_memset(void *s, int c, size_t n);

/**
 * @brief Azzera i primi n byte di un'area di memoria.
 *
 * @param s Area da azzerare. Non puo' essere NULL e deve essere grande almeno n
 *        byte.
 * @param n Numero di byte da azzerare.
 */
void	ft_bzero(void *s, size_t n);

/**
 * @brief Copia n byte da un'area di memoria a un'altra.
 *
 * Le due aree non devono sovrapporsi: se lo fanno il risultato non e'
 * prevedibile e serve ft_memmove.
 *
 * @param dest Area di destinazione, grande almeno n byte.
 * @param src Area di partenza, grande almeno n byte.
 * @param n Numero di byte da copiare.
 * @return void * dest, oppure NULL se dest e src sono entrambi NULL.
 */
void	*ft_memcpy(void *dest, const void *src, size_t n);

/**
 * @brief Copia n byte fra due aree di memoria anche se si sovrappongono.
 *
 * Sceglie il verso della copia in base alla posizione reciproca delle due aree,
 * cosi' nessun byte viene sovrascritto prima di essere letto.
 *
 * @param dest Area di destinazione, grande almeno n byte.
 * @param src Area di partenza, grande almeno n byte.
 * @param n Numero di byte da copiare.
 * @return void * dest, oppure NULL se dest e src sono entrambi NULL.
 */
void	*ft_memmove(void *dest, const void *src, size_t n);

/**
 * @brief Copia una stringa in un'altra scrivendo al massimo size byte.
 *
 * @param dst Stringa di destinazione, grande almeno size byte.
 * @param src Stringa da copiare. Non puo' essere NULL.
 * @param size Spazio disponibile in dst, terminatore compreso.
 * @return size_t La lunghezza di src, cioe' quanti caratteri servivano davvero.
 */
size_t	ft_strlcpy(char *dst, const char *src, size_t size);

/**
 * @brief Concatena una stringa in coda a un'altra senza superare una
 *        dimensione.
 *
 * Quando scrive, chiude sempre il risultato con il terminatore. Con size
 * uguale a 0 non scrive niente e dst resta com'e'.
 *
 * @param dst Stringa gia' valida, grande almeno size byte.
 * @param src Stringa da accodare. Non puo' essere NULL.
 * @param size Spazio totale disponibile in dst, terminatore compreso.
 * @return size_t La lunghezza che il risultato avrebbe avuto con spazio a
 *         sufficienza.
 */
size_t	ft_strlcat(char *dst, const char *src, size_t size);

/**
 * @brief Trasforma una lettera minuscola nella corrispondente maiuscola.
 *
 * @param c Carattere da convertire, passato come unsigned char o EOF.
 * @return int La maiuscola, oppure c invariato se non era una minuscola.
 */
int		ft_toupper(int c);

/**
 * @brief Trasforma una lettera maiuscola nella corrispondente minuscola.
 *
 * @param c Carattere da convertire, passato come unsigned char o EOF.
 * @return int La minuscola, oppure c invariato se non era una maiuscola.
 */
int		ft_tolower(int c);

/**
 * @brief Cerca la prima occorrenza di un carattere in una stringa.
 *
 * Il terminatore fa parte della stringa, quindi cercare '\0' trova la fine.
 *
 * @param s Stringa in cui cercare. Puo' essere NULL.
 * @param c Carattere da cercare, confrontato come unsigned char.
 * @return char * L'indirizzo dell'occorrenza, NULL se non c'e' o se s e' NULL.
 */
char	*ft_strchr(const char *s, int c);

/**
 * @brief Cerca l'ultima occorrenza di un carattere in una stringa.
 *
 * La ricerca parte dal terminatore e va all'indietro, quindi cercare '\0'
 * trova la fine della stringa.
 *
 * @param s Stringa in cui cercare. Non puo' essere NULL.
 * @param c Carattere da cercare, ridotto a char.
 * @return char * L'indirizzo dell'ultima occorrenza, NULL se non c'e'.
 */
char	*ft_strrchr(const char *s, int c);

/**
 * @brief Confronta due stringhe al massimo per n caratteri.
 *
 * Il confronto si ferma al primo carattere diverso, al terminatore o dopo n
 * caratteri, quello che viene prima.
 *
 * @param s1 Prima stringa. Non puo' essere NULL.
 * @param s2 Seconda stringa. Non puo' essere NULL.
 * @param n Numero massimo di caratteri da confrontare.
 * @return int 0 se il tratto confrontato e' uguale o se n vale 0, altrimenti la
 *         differenza fra i due caratteri letti come unsigned char.
 */
int		ft_strncmp(const char *s1, const char *s2, size_t n);

/**
 * @brief Cerca un byte nei primi n byte di un'area di memoria.
 *
 * @param s Area in cui cercare. Non puo' essere NULL e deve essere grande
 *        almeno n byte.
 * @param c Byte da cercare, confrontato come unsigned char.
 * @param n Numero di byte da esaminare.
 * @return void * L'indirizzo della prima occorrenza, NULL se il byte non c'e'.
 */
void	*ft_memchr(const void *s, int c, size_t n);

/**
 * @brief Confronta byte per byte le prime n posizioni di due aree di memoria.
 *
 * @param s1 Prima area. Non puo' essere NULL e deve essere grande almeno n
 *        byte.
 * @param s2 Seconda area, con gli stessi vincoli.
 * @param n Numero di byte da confrontare.
 * @return int 0 se il tratto confrontato e' uguale o se n vale 0, altrimenti la
 *         differenza fra i primi due byte diversi.
 */
int		ft_memcmp(const void *s1, const void *s2, size_t n);

/**
 * @brief Cerca una stringa dentro i primi len caratteri di un'altra.
 *
 * @param big Stringa in cui cercare. Non puo' essere NULL.
 * @param little Stringa da cercare. Non puo' essere NULL.
 * @param len Numero massimo di caratteri di big da esaminare.
 * @return char * L'indirizzo dell'occorrenza dentro big, big stesso se little
 *         e' vuota, NULL se non la trova.
 */
char	*ft_strnstr(const char *big, const char *little, size_t len);

/**
 * @brief Converte l'inizio di una stringa nell'intero corrispondente.
 *
 * Salta gli spazi bianchi iniziali (' ' e i codici da 9 a 13), accetta un solo
 * segno + o -, poi legge le cifre finche' ne trova. L'overflow non e' gestito:
 * oltre i limiti di int il risultato non ha significato.
 *
 * @param nptr Stringa da convertire. Non puo' essere NULL.
 * @return int Il numero letto, 0 se non e' stata trovata nessuna cifra.
 */
int		ft_atoi(const char *nptr);

/**
 * @brief Alloca un blocco di memoria gia' azzerato.
 *
 * Se nmemb o size valgono 0 il risultato e' quello di malloc(0).
 *
 * @param nmemb Numero di elementi.
 * @param size Dimensione in byte di un elemento.
 * @return void * L'area azzerata, da liberare con free; NULL se l'allocazione
 *         fallisce o se il prodotto supera 4294967295 byte.
 */
void	*ft_calloc(size_t nmemb, size_t size);

/**
 * @brief Crea una copia di una stringa in memoria appena allocata.
 *
 * @param s Stringa da copiare. Non puo' essere NULL.
 * @return char * La copia, da liberare con free; NULL se l'allocazione
 *         fallisce.
 */
char	*ft_strdup(const char *s);

/**
 * @brief Estrae una sottostringa a partire da una posizione.
 *
 * @param s Stringa di partenza. Non puo' essere NULL.
 * @param start Posizione da cui cominciare.
 * @param len Numero massimo di caratteri da copiare.
 * @return char * La sottostringa allocata, da liberare con free; una stringa
 *         vuota se start raggiunge o supera la fine di s; NULL se
 *         l'allocazione fallisce.
 */
char	*ft_substr(char const *s, unsigned int start, size_t len);

/**
 * @brief Unisce due stringhe in una nuova.
 *
 * Le stringhe di partenza non vengono liberate.
 *
 * @param s1 Prima stringa. Puo' essere NULL: conta come stringa vuota.
 * @param s2 Seconda stringa. Puo' essere NULL: conta come stringa vuota.
 * @return char * La stringa unita, da liberare con free; NULL se l'allocazione
 *         fallisce.
 */
char	*ft_strjoin(char *s1, char *s2);

/**
 * @brief Toglie da una stringa i caratteri iniziali e finali di un insieme.
 *
 * @param s1 Stringa da ripulire. Non puo' essere NULL.
 * @param set Insieme dei caratteri da togliere. Non puo' essere NULL.
 * @return char * La stringa ripulita, da liberare con free; NULL se
 *         l'allocazione fallisce.
 */
char	*ft_strtrim(char const *s1, char const *set);

/**
 * @brief Spezza una stringa in parole separate da un delimitatore.
 *
 * @param s Stringa da spezzare. Non puo' essere NULL.
 * @param c Carattere separatore.
 * @return char ** Una matrice terminata da NULL, da liberare stringa per
 *         stringa e poi nell'insieme; NULL se un'allocazione fallisce.
 */
char	**ft_split(char const *s, char c);

/**
 * @brief Costruisce la rappresentazione decimale di un intero in una nuova
 *        stringa.
 *
 * @param n Numero da convertire, INT_MIN compreso.
 * @return char * La stringa allocata, da liberare con free; NULL se
 *         l'allocazione fallisce.
 */
char	*ft_itoa(int n);

/**
 * @brief Costruisce una nuova stringa trasformando ogni carattere di un'altra.
 *
 * @param s Stringa di partenza. Non puo' essere NULL.
 * @param f Funzione chiamata con l'indice e il carattere, restituisce il
 *        carattere da scrivere.
 * @return char * La nuova stringa, da liberare con free; NULL se l'allocazione
 *         fallisce.
 */
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));

/**
 * @brief Applica una funzione a ogni carattere di una stringa, sul posto.
 *
 * @param s Stringa da percorrere. Non puo' essere NULL.
 * @param f Funzione chiamata con l'indice e l'indirizzo del carattere, cosi'
 *        puo' modificarlo.
 */
void	ft_striteri(char *s, void (*f)(unsigned int, char*));

/**
 * @brief Scrive un carattere su un descrittore di file.
 *
 * @param c Carattere da scrivere.
 * @param fd Descrittore aperto in scrittura.
 */
void	ft_putchar_fd(char c, int fd);

/**
 * @brief Scrive una stringa su un descrittore di file, senza a capo finale.
 *
 * @param s Stringa da scrivere. Se e' NULL non viene scritto niente.
 * @param fd Descrittore aperto in scrittura.
 */
void	ft_putstr_fd(char *s, int fd);

/**
 * @brief Scrive una stringa su un descrittore di file, seguita da un a capo.
 *
 * @param s Stringa da scrivere. Se e' NULL viene scritto solo l'a capo.
 * @param fd Descrittore aperto in scrittura.
 */
void	ft_putendl_fd(char *s, int fd);

/**
 * @brief Scrive un intero in base 10 su un descrittore di file.
 *
 * @param n Numero da scrivere; INT_MIN e' gestito passando per un long.
 * @param fd Descrittore aperto in scrittura.
 */
void	ft_putnbr_fd(int n, int fd);

/* ========================================================================== */
/*                          MODULO 2 - ft_printf                              */
/* ========================================================================== */

/**
 * @brief Stampa su standard output una stringa di formato con i suoi argomenti.
 *
 * Gestisce le conversioni c, s, p, d, i, u, x, X e il percento raddoppiato. Non
 * gestisce flag, ampiezza e precisione. Un percento in fondo alla stringa, a
 * cui non segue nessuna lettera, ferma la stampa: non viene stampato e il
 * conteggio restituito e' quello dei caratteri usciti fino a li'.
 *
 * @param str Stringa di formato, seguita dagli argomenti richiesti dalle
 *        conversioni.
 * @return int Il numero di caratteri stampati, 0 se il formato e' NULL o vuoto.
 */
int		ft_printf(const char *str, ...);

/**
 * @brief Esegue una singola conversione di ft_printf.
 *
 * Riconosce c, s, p, d, i, u, x, X e il percento raddoppiato.
 *
 * @param argl Elenco degli argomenti variabili, passato per indirizzo perche'
 *        la funzione lo fa avanzare.
 * @param c Lettera che segue il segno di percento.
 * @return int I caratteri stampati, 0 se la conversione non e' riconosciuta.
 */
int		ft_conv_printf(va_list *argl, int c);

/**
 * @brief Scrive un carattere su standard output.
 *
 * @param c Carattere da stampare.
 * @return int Sempre 1, cioe' i caratteri scritti.
 */
int		ft_putchar(char c);

/**
 * @brief Stampa un numero senza segno in una base qualsiasi.
 *
 * @param n Numero da stampare.
 * @param base Stringa con le cifre della base, dalla piu' piccola.
 * @param len Lunghezza di base, che fa anche da valore della base.
 * @return int Il numero di caratteri stampati.
 */
int		ft_putnbr_b(unsigned int n, char *base, unsigned int len);

/**
 * @brief Stampa un intero in base 10 su standard output.
 *
 * @param n Numero da stampare; INT_MIN e' gestito passando per un long.
 * @return int Il numero di caratteri stampati, segno meno compreso.
 */
int		ft_putnbr(int n);

/**
 * @brief Stampa un indirizzo in esadecimale preceduto da 0x, come fa %p.
 *
 * @param ptr Indirizzo da stampare. Puo' essere NULL.
 * @param base Stringa con le sedici cifre esadecimali.
 * @return int Il numero di caratteri stampati; 5 se ptr e' NULL, perche' in
 *         quel caso stampa (nil).
 */
int		ft_putptr(void *ptr, char *base);

/**
 * @brief Stampa una stringa su standard output.
 *
 * @param s Stringa da stampare. Puo' essere NULL.
 * @return int I caratteri stampati; 6 se s e' NULL, perche' in quel caso stampa
 *         (null).
 */
int		ft_putstr(char *s);

/* ========================================================================== */
/*                       MODULO 3 - get_next_line                             */
/*   Versione con uno stato per ogni file descriptor: piu' file possono       */
/*   essere letti contemporaneamente.                                         */
/* ========================================================================== */

/**
 * @brief Restituisce la riga successiva di un file, a capo finale compreso.
 *
 * Quello che viene letto oltre la riga resta conservato in un array statico
 * indicizzato dal descrittore, quindi piu' file possono essere letti
 * contemporaneamente senza che le letture si mescolino. Richiede BUFFER_SIZE
 * maggiore di zero.
 *
 * @param fd Descrittore aperto in lettura, minore di 4096.
 * @return char * La riga allocata, da liberare con free; NULL a fine file, se
 *         fd non e' valido o in caso di errore.
 */
char	*get_next_line(int fd);

/* ========================================================================== */
/*                    MODULO 4 - collegamento fra i moduli                    */
/* ========================================================================== */

/**
 * @brief Da' il nome e la versione della libreria.
 *
 * @return const char * Una stringa costante, da non liberare.
 */
const char	*ft_mega_version(void);

/**
 * @brief Legge una riga con get_next_line e la stampa con ft_printf.
 *
 * Mette in comunicazione il modulo get_next_line con il modulo ft_printf; la
 * riga letta viene liberata prima di restituire il risultato.
 *
 * @param fd Descrittore aperto in lettura.
 * @return int I caratteri stampati, -1 a fine file o in caso di errore.
 */
int			ft_mega_print_next_line(int fd);

/**
 * @brief Stampa tutto il file leggendolo riga per riga fino alla fine.
 *
 * @param fd Descrittore aperto in lettura.
 * @return int Il totale dei caratteri stampati.
 */
int			ft_mega_print_file(int fd);

/* ===== BONUS - inizio ===================================================== */
/*   Lista concatenata semplice. Disponibili solo con `make bonus`.           */

/**
 * @brief Crea un elemento di lista che punta a un contenuto.
 *
 * @param content Dato da agganciare; viene puntato, non copiato.
 * @return t_list * Il nuovo elemento, con next a NULL; NULL se l'allocazione
 *         fallisce.
 */
t_list	*ft_lstnew(void *content);

/**
 * @brief Aggancia un elemento in testa a una lista, che diventa la nuova testa.
 *
 * @param lst Indirizzo del puntatore alla testa. Non puo' essere NULL.
 * @param new Elemento gia' creato da agganciare. Non puo' essere NULL.
 */
void	ft_lstadd_front(t_list **lst, t_list *new);

/**
 * @brief Conta gli elementi di una lista.
 *
 * @param lst Testa della lista.
 * @return int Il numero di elementi, 0 se la lista e' vuota.
 */
int		ft_lstsize(t_list *lst);

/**
 * @brief Cerca l'ultimo elemento di una lista.
 *
 * @param lst Testa della lista.
 * @return t_list * L'ultimo elemento, NULL se la lista e' vuota.
 */
t_list	*ft_lstlast(t_list *lst);

/**
 * @brief Aggancia un elemento in fondo a una lista.
 *
 * @param lst Indirizzo del puntatore alla testa. Se e' NULL non succede niente.
 * @param new Elemento gia' creato da agganciare. Se e' NULL non succede niente.
 */
void	ft_lstadd_back(t_list **lst, t_list *new);

/**
 * @brief Libera un singolo elemento e il suo contenuto.
 *
 * Il resto della lista non viene toccato: e' il chiamante che deve aver gia'
 * ricucito i collegamenti.
 *
 * @param lst Elemento da eliminare. Se e' NULL non succede niente.
 * @param del Funzione che sa liberare il contenuto dell'elemento.
 */
void	ft_lstdelone(t_list *lst, void (*del)(void*));

/**
 * @brief Svuota una lista liberando contenuti ed elementi.
 *
 * Se uno dei due parametri e' NULL la funzione non fa niente.
 *
 * @param lst Indirizzo del puntatore alla testa; viene azzerato alla fine.
 * @param del Funzione che sa liberare il contenuto di un elemento.
 */
void	ft_lstclear(t_list **lst, void (*del)(void*));

/**
 * @brief Applica una funzione al contenuto di ogni elemento della lista.
 *
 * @param lst Testa della lista.
 * @param f Funzione chiamata con il contenuto di ogni elemento. Non puo'
 *        essere NULL.
 */
void	ft_lstiter(t_list *lst, void (*f)(void *));

/**
 * @brief Costruisce una nuova lista trasformando il contenuto di ogni elemento.
 *
 * Se un'allocazione fallisce a meta' strada, tutto il lavoro gia' fatto viene
 * liberato prima di restituire NULL.
 *
 * @param lst Lista di partenza. Non puo' essere NULL.
 * @param f Funzione che trasforma il contenuto di un elemento.
 * @param del Funzione che sa liberare un contenuto, usata se qualcosa va
 *        storto.
 * @return t_list * La nuova lista, NULL se un parametro manca o se
 *         un'allocazione fallisce.
 */
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

/* ===== BONUS - fine ======================================================= */

/* ----- src/libft/ft_atoi.c ----- */

/**
 * @brief Converte l'inizio di una stringa nell'intero corrispondente.
 *
 * Salta gli spazi bianchi iniziali (' ' e i codici da 9 a 13), accetta un solo
 * segno + o -, poi legge le cifre finche' ne trova. L'overflow non e' gestito:
 * oltre i limiti di int il risultato non ha significato.
 *
 * @param nptr Stringa da convertire. Non puo' essere NULL.
 * @return int Il numero letto, 0 se non e' stata trovata nessuna cifra.
 */
int	ft_atoi(const char *nptr)
{
	int	sign;
	int	i;
	int	num;

	i = 0;
	num = 0;
	sign = 1;
	while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		num *= 10;
		num += nptr[i] - '0';
		i++;
	}
	return (num * sign);
}

/* ----- src/libft/ft_bzero.c ----- */

/**
 * @brief Azzera i primi n byte di un'area di memoria.
 *
 * @param s Area da azzerare. Non puo' essere NULL e deve essere grande almeno n
 *        byte.
 * @param n Numero di byte da azzerare.
 */
void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		*(unsigned char *)(s + i) = '\0';
		i++;
	}
}

/* ----- src/libft/ft_isalnum.c ----- */

/**
 * @brief Dice se un carattere e' una lettera o una cifra.
 *
 * @param c Carattere da esaminare, passato come unsigned char o EOF.
 * @return int 1 se il carattere e' alfanumerico, 0 altrimenti.
 */
int	ft_isalnum(int c)
{
	if (ft_isalpha(c) || ft_isdigit(c))
		return (1);
	return (0);
}

/* ----- src/libft/ft_isalpha.c ----- */

/**
 * @brief Dice se un carattere e' una lettera dell'alfabeto.
 *
 * @param c Carattere da esaminare, passato come unsigned char o EOF.
 * @return int 1 se il carattere e' una lettera maiuscola o minuscola, 0
 *         altrimenti.
 */
int	ft_isalpha(int c)
{
	if ((c >= 97 && c <= 122) || (c >= 65 && c <= 90))
		return (1);
	return (0);
}

/* ----- src/libft/ft_isascii.c ----- */

/**
 * @brief Dice se un carattere appartiene alla tabella ASCII.
 *
 * @param c Intero da esaminare.
 * @return int 1 se il valore sta fra 0 e 127 compresi, 0 altrimenti.
 */
int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	return (0);
}

/* ----- src/libft/ft_isdigit.c ----- */

/**
 * @brief Dice se un carattere e' una cifra decimale.
 *
 * @param c Carattere da esaminare, passato come unsigned char o EOF.
 * @return int 1 se il carattere sta fra '0' e '9', 0 altrimenti.
 */
int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

/* ----- src/libft/ft_isprint.c ----- */

/**
 * @brief Dice se un carattere e' stampabile, spazio compreso.
 *
 * @param c Carattere da esaminare, passato come unsigned char o EOF.
 * @return int 1 se il valore sta fra 32 e 126 compresi, 0 altrimenti.
 */
int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
		return (1);
	return (0);
}

/* ----- src/libft/ft_itoa.c ----- */

/**
 * @brief Conta i caratteri necessari a scrivere un numero in base 10.
 *
 * Funzione di servizio di ft_itoa, serve a sapere quanta memoria allocare.
 *
 * @param n Numero da misurare, segno compreso.
 * @return int Il numero di caratteri, segno meno incluso; 1 se n vale 0.
 */
static int	ft_dim(long int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		i += 1;
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

/**
 * @brief Costruisce la rappresentazione decimale di un intero in una nuova
 *        stringa.
 *
 * @param n Numero da convertire, INT_MIN compreso.
 * @return char * La stringa allocata, da liberare con free; NULL se
 *         l'allocazione fallisce.
 */
char	*ft_itoa(int n)
{
	int			d;
	long int	num;
	char		*str;

	d = ft_dim(n);
	str = (char *)ft_calloc((d + 1), sizeof(char));
	if (!str)
		return (NULL);
	if (n < 0)
	{
		str[0] = '-';
		num = -(long int)n;
	}
	else
		num = (long int)n;
	if (num == 0)
		str[0] = '0';
	str[d] = '\0';
	while (num != 0)
	{
		str[d - 1] = (num % 10) + '0';
		num /= 10;
		d--;
	}
	return (str);
}

/* ----- src/libft/ft_memchr.c ----- */

/**
 * @brief Cerca un byte nei primi n byte di un'area di memoria.
 *
 * @param s Area in cui cercare. Non puo' essere NULL e deve essere grande
 *        almeno n byte.
 * @param c Byte da cercare, confrontato come unsigned char.
 * @param n Numero di byte da esaminare.
 * @return void * L'indirizzo della prima occorrenza, NULL se il byte non c'e'.
 */
void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*str;

	str = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (str[i] == (unsigned char)c)
			return (str + i);
		i++;
	}
	return (NULL);
}

/* ----- src/libft/ft_memcmp.c ----- */

/**
 * @brief Confronta byte per byte le prime n posizioni di due aree di memoria.
 *
 * @param s1 Prima area. Non puo' essere NULL e deve essere grande almeno n
 *        byte.
 * @param s2 Seconda area, con gli stessi vincoli.
 * @param n Numero di byte da confrontare.
 * @return int 0 se il tratto confrontato e' uguale o se n vale 0, altrimenti la
 *         differenza fra i primi due byte diversi.
 */
int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*st1;
	unsigned char	*st2;

	st1 = (unsigned char *)s1;
	st2 = (unsigned char *)s2;
	i = 0;
	if (n == 0)
		return (0);
	while (st1[i] == st2[i] && i < n - 1)
		i++;
	return (st1[i] - st2[i]);
}

/* ----- src/libft/ft_memcpy.c ----- */

/**
 * @brief Copia n byte da un'area di memoria a un'altra.
 *
 * Le due aree non devono sovrapporsi: se lo fanno il risultato non e'
 * prevedibile e serve ft_memmove.
 *
 * @param dest Area di destinazione, grande almeno n byte.
 * @param src Area di partenza, grande almeno n byte.
 * @param n Numero di byte da copiare.
 * @return void * dest, oppure NULL se dest e src sono entrambi NULL.
 */
void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (dest == NULL && src == NULL)
		return (NULL);
	while (i < n)
	{
		*(unsigned char *)(dest + i) = *(unsigned char *)(src + i);
		i++;
	}
	return (dest);
}

/* ----- src/libft/ft_memmove.c ----- */

/**
 * @brief Copia n byte fra due aree di memoria anche se si sovrappongono.
 *
 * Sceglie il verso della copia in base alla posizione reciproca delle due aree,
 * cosi' nessun byte viene sovrascritto prima di essere letto.
 *
 * @param dest Area di destinazione, grande almeno n byte.
 * @param src Area di partenza, grande almeno n byte.
 * @param n Numero di byte da copiare.
 * @return void * dest, oppure NULL se dest e src sono entrambi NULL.
 */
void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*s;
	char	*d;
	size_t	i;

	s = (char *)src;
	d = (char *)dest;
	i = 0;
	if (!src && !dest)
		return (NULL);
	if (d > s)
	{
		while (n-- > 0)
			d[n] = s[n];
	}
	else
	{
		while (i < n)
		{
			d[i] = s[i];
			i++;
		}
	}
	return (dest);
}

/* ----- src/libft/ft_memset.c ----- */

/**
 * @brief Riempie i primi n byte di un'area di memoria con un byte dato.
 *
 * @param s Area da riempire. Non puo' essere NULL e deve essere grande almeno n
 *        byte.
 * @param c Valore da scrivere, ridotto a unsigned char.
 * @param n Numero di byte da riempire.
 * @return void * s.
 */
void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		*(unsigned char *)(s + i) = (unsigned char)c;
		i++;
	}
	return (s);
}

/* ----- src/libft/ft_putchar_fd.c ----- */

/**
 * @brief Scrive un carattere su un descrittore di file.
 *
 * @param c Carattere da scrivere.
 * @param fd Descrittore aperto in scrittura.
 */
void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

/* ----- src/libft/ft_putendl_fd.c ----- */

/**
 * @brief Scrive una stringa su un descrittore di file, seguita da un a capo.
 *
 * @param s Stringa da scrivere. Se e' NULL viene scritto solo l'a capo.
 * @param fd Descrittore aperto in scrittura.
 */
void	ft_putendl_fd(char *s, int fd)
{
	ft_putstr_fd(s, fd);
	ft_putchar_fd('\n', fd);
}

/* ----- src/libft/ft_putnbr_fd.c ----- */

/**
 * @brief Gestisce il caso limite dello zero per ft_putnbr_fd.
 *
 * Senza questo controllo il ciclo delle cifre non produrrebbe niente.
 *
 * @param n Numero gia' reso positivo dal chiamante.
 * @param fd Descrittore aperto in scrittura.
 * @return int 1 se n era 0 e lo zero e' stato scritto, 0 altrimenti.
 */
static int	ft_is_special(long n, int fd)
{
	if (n == 0)
	{
		write(fd, "0", 1);
		return (1);
	}
	return (0);
}

/**
 * @brief Scrive un intero in base 10 su un descrittore di file.
 *
 * @param n Numero da scrivere; INT_MIN e' gestito passando per un long.
 * @param fd Descrittore aperto in scrittura.
 */
void	ft_putnbr_fd(int n, int fd)
{
	int		arr[12];
	int		i;
	long	num;

	i = 0;
	num = (long)n;
	if (num < 0)
	{
		num *= -1;
		write(fd, "-", 1);
	}
	if (ft_is_special(num, fd))
	{
		return ;
	}
	while (num > 0)
	{
		arr[i++] = (num % 10) + '0';
		num /= 10;
	}
	while (--i >= 0)
	{
		write(fd, &arr[i], 1);
	}
}

/* ----- src/libft/ft_putstr_fd.c ----- */

/**
 * @brief Scrive una stringa su un descrittore di file, senza a capo finale.
 *
 * @param s Stringa da scrivere. Se e' NULL non viene scritto niente.
 * @param fd Descrittore aperto in scrittura.
 */
void	ft_putstr_fd(char *s, int fd)
{
	write(fd, s, ft_strlen(s));
}

/* ----- src/libft/ft_split.c ----- */

/**
 * @brief Conta i gruppi di caratteri separati da un delimitatore.
 *
 * Funzione di servizio di ft_split, serve a dimensionare la matrice.
 *
 * @param s Stringa da esaminare. Non puo' essere NULL.
 * @param c Carattere separatore.
 * @return int Il numero di parole trovate.
 */
static int	ft_count_words(char *s, char c)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c && s[i] != '\0')
			i++;
		if (s[i] != c && s[i] != '\0')
		{
			count++;
			while (s[i] != c && s[i] != '\0')
				i++;
		}
	}
	return (count);
}

/**
 * @brief Estrae in una nuova stringa la parola che inizia a una data posizione.
 *
 * @param s Stringa da cui estrarre. Non puo' essere NULL.
 * @param c Carattere separatore che chiude la parola.
 * @param index Posizione di partenza; viene spostata sul separatore finale.
 * @return char * La parola allocata, NULL se l'allocazione fallisce.
 */
static char	*ft_fill_matrix(char *s, char c, int *index)
{
	int		i;
	int		j;
	char	*word;

	i = *index;
	j = 0;
	while (s[i + j] != c && s[i + j] != '\0')
		j++;
	word = (char *)ft_calloc(j + 1, sizeof(char));
	if (!word)
		return (NULL);
	ft_strlcpy(word, s + i, j + 1);
	*index = i + j;
	return (word);
}

/**
 * @brief Libera una matrice di stringhe rimasta a meta'.
 *
 * Serve a ft_split per non perdere memoria quando un'allocazione fallisce prima
 * che la matrice sia completa.
 *
 * @param s Matrice da liberare.
 * @param w Indice dell'ultima stringa da liberare.
 * @return void * Sempre NULL, cosi' il chiamante puo' restituirlo direttamente.
 */
static void	*ft_free_matrix(char **s, int w)
{
	while (w >= 0)
	{
		free(s[w]);
		w--;
	}
	free(s);
	return (NULL);
}

/**
 * @brief Spezza una stringa in parole separate da un delimitatore.
 *
 * @param s Stringa da spezzare. Non puo' essere NULL.
 * @param c Carattere separatore.
 * @return char ** Una matrice terminata da NULL, da liberare stringa per
 *         stringa e poi nell'insieme; NULL se un'allocazione fallisce.
 */
char	**ft_split(char const *s, char c)
{
	int		nwords;
	char	**str;
	int		w;
	int		i;

	nwords = ft_count_words((char *)s, (char)c);
	str = (char **)ft_calloc(nwords + 1, sizeof(char *));
	if (!str)
		return (NULL);
	w = -1;
	i = 0;
	while (++w < nwords)
	{
		while (s[i] == c && s[i] != '\0')
			i++;
		if (s[i] != c && s[i] != '\0')
		{
			str[w] = ft_fill_matrix((char *)s, c, &i);
			if (str[w] == NULL)
				return (ft_free_matrix(str, w));
		}
	}
	str[w] = NULL;
	return (str);
}

/* ----- src/libft/ft_strdup.c ----- */

/**
 * @brief Crea una copia di una stringa in memoria appena allocata.
 *
 * @param s Stringa da copiare. Non puo' essere NULL.
 * @return char * La copia, da liberare con free; NULL se l'allocazione
 *         fallisce.
 */
char	*ft_strdup(const char *s)
{
	int		i;
	char	*result;

	i = 0;
	result = (char *)malloc(sizeof(char) * ft_strlen(s) + 1);
	if (!result)
		return (NULL);
	while (s[i] != '\0')
	{
		result[i] = s[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}

/* ----- src/libft/ft_striteri.c ----- */

/**
 * @brief Applica una funzione a ogni carattere di una stringa, sul posto.
 *
 * @param s Stringa da percorrere. Non puo' essere NULL.
 * @param f Funzione chiamata con l'indice e l'indirizzo del carattere, cosi'
 *        puo' modificarlo.
 */
void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		f(i, &s[i]);
		i++;
	}
	s[i] = '\0';
}

/* ----- src/libft/ft_strlcat.c ----- */

/**
 * @brief Concatena una stringa in coda a un'altra senza superare una
 *        dimensione.
 *
 * Quando scrive, chiude sempre il risultato con il terminatore. Con size
 * uguale a 0 non scrive niente e dst resta com'e'.
 *
 * @param dst Stringa gia' valida, grande almeno size byte.
 * @param src Stringa da accodare. Non puo' essere NULL.
 * @param size Spazio totale disponibile in dst, terminatore compreso.
 * @return size_t La lunghezza che il risultato avrebbe avuto con spazio a
 *         sufficienza.
 */
size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	count;
	size_t	d_len;
	size_t	s_len;
	size_t	i;

	count = 0;
	d_len = ft_strlen(dst);
	i = d_len;
	s_len = ft_strlen(src);
	if (size <= 0)
		return (s_len + size);
	while (i < (size - 1) && src[count] != '\0')
	{
		dst[i] = src[count];
		i++;
		count++;
	}
	dst[i] = '\0';
	if (size < d_len)
		return (s_len + size);
	else
		return (d_len + s_len);
}

/* ----- src/libft/ft_strlcpy.c ----- */

/**
 * @brief Copia una stringa in un'altra scrivendo al massimo size byte.
 *
 * @param dst Stringa di destinazione, grande almeno size byte.
 * @param src Stringa da copiare. Non puo' essere NULL.
 * @param size Spazio disponibile in dst, terminatore compreso.
 * @return size_t La lunghezza di src, cioe' quanti caratteri servivano davvero.
 */
size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	count;

	count = 0;
	if (size != 0)
	{
		while (count < (size - 1) && src[count] != '\0')
		{
			dst[count] = src[count];
			count++;
		}
		dst[count] = '\0';
	}
	return (ft_strlen(src));
}

/* ----- src/libft/ft_strlen.c ----- */

/**
 * @brief Conta i caratteri di una stringa fino al terminatore, escluso.
 *
 * @param s Stringa da misurare. Puo' essere NULL: in quel caso non viene letto
 *        niente.
 * @return size_t La lunghezza di s, 0 se s e' NULL.
 */
size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s && s[i] != '\0')
		i++;
	return (i);
}

/* ----- src/libft/ft_strmapi.c ----- */

/**
 * @brief Costruisce una nuova stringa trasformando ogni carattere di un'altra.
 *
 * @param s Stringa di partenza. Non puo' essere NULL.
 * @param f Funzione chiamata con l'indice e il carattere, restituisce il
 *        carattere da scrivere.
 * @return char * La nuova stringa, da liberare con free; NULL se l'allocazione
 *         fallisce.
 */
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*strmp;
	int		i;

	i = 0;
	strmp = (char *)malloc(sizeof(char) * ft_strlen(s) + 1);
	if (!strmp)
		return (NULL);
	while (s[i] != '\0')
	{
		strmp[i] = f(i, s[i]);
		i++;
	}
	strmp[i] = '\0';
	return (strmp);
}

/* ----- src/libft/ft_strncmp.c ----- */

/**
 * @brief Confronta due stringhe al massimo per n caratteri.
 *
 * Il confronto si ferma al primo carattere diverso, al terminatore o dopo n
 * caratteri, quello che viene prima.
 *
 * @param s1 Prima stringa. Non puo' essere NULL.
 * @param s2 Seconda stringa. Non puo' essere NULL.
 * @param n Numero massimo di caratteri da confrontare.
 * @return int 0 se il tratto confrontato e' uguale o se n vale 0, altrimenti la
 *         differenza fra i due caratteri letti come unsigned char.
 */
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (i < n - 1 && s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

/* ----- src/libft/ft_strnstr.c ----- */

/**
 * @brief Cerca una stringa dentro i primi len caratteri di un'altra.
 *
 * @param big Stringa in cui cercare. Non puo' essere NULL.
 * @param little Stringa da cercare. Non puo' essere NULL.
 * @param len Numero massimo di caratteri di big da esaminare.
 * @return char * L'indirizzo dell'occorrenza dentro big, big stesso se little
 *         e' vuota, NULL se non la trova.
 */
char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	char	*s1;
	char	*s2;

	i = 0;
	s1 = (char *)big;
	s2 = (char *)little;
	if (!*s2)
		return (s1);
	while (s1[i] && i < len)
	{
		if (s1[i] == *s2)
		{
			j = 0;
			while (s1[i + j] == s2[j] && s1[i + j] && (i + j) < len)
				j++;
			if (!s2[j])
				return (s1 + i);
		}
		i++;
	}
	return (NULL);
}

/* ----- src/libft/ft_strrchr.c ----- */

/**
 * @brief Cerca l'ultima occorrenza di un carattere in una stringa.
 *
 * La ricerca parte dal terminatore e va all'indietro, quindi cercare '\0'
 * trova la fine della stringa.
 *
 * @param s Stringa in cui cercare. Non puo' essere NULL.
 * @param c Carattere da cercare, ridotto a char.
 * @return char * L'indirizzo dell'ultima occorrenza, NULL se non c'e'.
 */
char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*tmp;
	char	ch;

	ch = (char)c;
	tmp = (char *)s;
	i = ft_strlen(tmp);
	while (tmp[i] != ch && i > 0)
		i--;
	if (i == 0 && tmp[i] != ch)
		return (NULL);
	return (tmp + i);
}

/* ----- src/libft/ft_strtrim.c ----- */

/**
 * @brief Dice se un carattere compare in un insieme.
 *
 * Funzione di servizio di ft_strtrim.
 *
 * @param s Insieme di caratteri. Non puo' essere NULL.
 * @param c Carattere da cercare.
 * @return int 1 se il carattere e' nell'insieme, 0 altrimenti.
 */
static int	ft_checkchr(char const *s, char const c)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
}

/**
 * @brief Toglie da una stringa i caratteri iniziali e finali di un insieme.
 *
 * @param s1 Stringa da ripulire. Non puo' essere NULL.
 * @param set Insieme dei caratteri da togliere. Non puo' essere NULL.
 * @return char * La stringa ripulita, da liberare con free; NULL se
 *         l'allocazione fallisce.
 */
char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	int		count;
	char	*strt;

	start = 0;
	while (s1[start] != '\0' && ft_checkchr(set, s1[start]))
		start++;
	end = ft_strlen(s1) - 1;
	while (end > start && ft_checkchr(set, s1[end]))
		end--;
	strt = (char *)malloc(sizeof(char) * (end - start) + 2);
	if (!strt)
		return (NULL);
	count = 0;
	while (start <= end)
	{
		strt[count] = s1[start];
		start++;
		count++;
	}
	strt[count] = '\0';
	return (strt);
}

/* ----- src/libft/ft_substr.c ----- */

/**
 * @brief Estrae una sottostringa a partire da una posizione.
 *
 * @param s Stringa di partenza. Non puo' essere NULL.
 * @param start Posizione da cui cominciare.
 * @param len Numero massimo di caratteri da copiare.
 * @return char * La sottostringa allocata, da liberare con free; una stringa
 *         vuota se start raggiunge o supera la fine di s; NULL se
 *         l'allocazione fallisce.
 */
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	i;

	i = -1;
	if (start > ft_strlen(s))
	{
		substr = malloc(sizeof(char) * 1);
		if (substr == NULL)
			return (NULL);
		*substr = '\0';
		return (substr);
	}
	s += start;
	if (ft_strlen(s) <= len)
		substr = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	else
		substr = (char *)malloc(sizeof(char) * (len + 1));
	if (!substr)
		return (NULL);
	while (s[++i] != '\0' && i < len)
		substr[i] = s[i];
	substr[i] = '\0';
	return (substr);
}

/* ----- src/libft/ft_tolower.c ----- */

/**
 * @brief Trasforma una lettera maiuscola nella corrispondente minuscola.
 *
 * @param c Carattere da convertire, passato come unsigned char o EOF.
 * @return int La minuscola, oppure c invariato se non era una maiuscola.
 */
int	ft_tolower(int c)
{
	if (c >= 65 && c <= 90)
		return (c + 32);
	return (c);
}

/* ----- src/libft/ft_toupper.c ----- */

/**
 * @brief Trasforma una lettera minuscola nella corrispondente maiuscola.
 *
 * @param c Carattere da convertire, passato come unsigned char o EOF.
 * @return int La maiuscola, oppure c invariato se non era una minuscola.
 */
int	ft_toupper(int c)
{
	if (c >= 97 && c <= 122)
		return (c - 32);
	return (c);
}

/* ----- src/ft_printf/ft_conv_printf.c ----- */

/**
 * @brief Esegue una singola conversione di ft_printf.
 *
 * Riconosce c, s, p, d, i, u, x, X e il percento raddoppiato.
 *
 * @param argl Elenco degli argomenti variabili, passato per indirizzo perche'
 *        la funzione lo fa avanzare.
 * @param c Lettera che segue il segno di percento.
 * @return int I caratteri stampati, 0 se la conversione non e' riconosciuta.
 */
int	ft_conv_printf(va_list *argl, int c)
{
	int	i;

	if (c == 'c')
		i = ft_putchar((int)va_arg(*argl, int));
	else if (c == 's')
		i = ft_putstr(va_arg(*argl, char *));
	else if (c == 'p')
		i = ft_putptr(va_arg(*argl, void *), "0123456789abcdef");
	else if (c == 'd' || c == 'i')
		i = ft_putnbr(va_arg(*argl, int));
	else if (c == 'u')
		i = ft_putnbr_b((unsigned int)va_arg(*argl, unsigned int),
				"0123456789", 10);
	else if (c == 'x')
		i = ft_putnbr_b((unsigned int)va_arg(*argl, unsigned int),
				"0123456789abcdef", 16);
	else if (c == 'X')
		i = ft_putnbr_b((unsigned int)va_arg(*argl, unsigned int),
				"0123456789ABCDEF", 16);
	else if (c == '%')
		i = ft_putchar('%');
	else
		return (0);
	return (i);
}

/* ----- src/ft_printf/ft_printf.c ----- */

/**
 * @brief Stampa su standard output una stringa di formato con i suoi argomenti.
 *
 * Gestisce le conversioni c, s, p, d, i, u, x, X e il percento raddoppiato. Non
 * gestisce flag, ampiezza e precisione. Un percento in fondo alla stringa, a
 * cui non segue nessuna lettera, ferma la stampa: non viene stampato e il
 * conteggio restituito e' quello dei caratteri usciti fino a li'.
 *
 * @param str Stringa di formato, seguita dagli argomenti richiesti dalle
 *        conversioni.
 * @return int Il numero di caratteri stampati, 0 se il formato e' NULL o vuoto.
 */
int	ft_printf(const char *str, ...)
{
	va_list	argl;
	int		i;
	int		count;

	i = 0;
	count = 0;
	if (!str || !*str)
		return (0);
	va_start(argl, str);
	while (str[i] != '\0')
	{
		if (str[i] == '%' && str[i + 1] == '\0')
			break ;
		if (str[i] == '%')
			count += ft_conv_printf(&argl, str[++i]);
		else
		{
			ft_putchar(str[i]);
			count++;
		}
		i++;
	}
	va_end(argl);
	return (count);
}

/* ----- src/ft_printf/ft_putchar.c ----- */

/**
 * @brief Scrive un carattere su standard output.
 *
 * @param c Carattere da stampare.
 * @return int Sempre 1, cioe' i caratteri scritti.
 */
int	ft_putchar(char c)
{
	write(1, &c, 1);
	return (1);
}

/* ----- src/ft_printf/ft_putnbr_b.c ----- */

/**
 * @brief Stampa un numero senza segno in una base qualsiasi.
 *
 * @param n Numero da stampare.
 * @param base Stringa con le cifre della base, dalla piu' piccola.
 * @param len Lunghezza di base, che fa anche da valore della base.
 * @return int Il numero di caratteri stampati.
 */
int	ft_putnbr_b(unsigned int n, char *base, unsigned int len)
{
	int		count;

	count = 0;
	if (n >= len)
	{
		count += ft_putnbr_b(n / len, base, len);
		n %= len;
	}
	if (n < len)
	{
		ft_putchar(base[n % len]);
		count++;
	}
	return (count);
}

/* ----- src/ft_printf/ft_putnbr.c ----- */

/**
 * @brief Stampa un intero in base 10 su standard output.
 *
 * @param n Numero da stampare; INT_MIN e' gestito passando per un long.
 * @return int Il numero di caratteri stampati, segno meno compreso.
 */
int	ft_putnbr(int n)
{
	int		count;
	long	num;

	count = 0;
	num = (long)n;
	if (num < 0)
	{
		num *= -1;
		ft_putchar('-');
		count++;
	}
	if (num >= 10)
	{
		count += ft_putnbr(num / 10);
		num %= 10;
	}
	if (num < 10)
	{
		ft_putchar(num + '0');
		count++;
	}
	return (count);
}

/* ----- src/ft_printf/ft_putptr.c ----- */

/**
 * @brief Stampa le cifre raccolte da ft_putptr, che le ha prodotte al
 *        contrario.
 *
 * @param i Quante cifre ci sono nell'array.
 * @param base Stringa con le sedici cifre esadecimali.
 * @param arr Cifre dalla meno significativa alla piu' significativa.
 * @return int Il numero di caratteri stampati.
 */
static int	ft_stampina(int i, char *base, int *arr)
{
	int	count;

	count = 0;
	while (--i >= 0)
	{
		ft_putchar(base[(int)arr[i]]);
		count++;
	}
	return (count);
}

/**
 * @brief Stampa un indirizzo in esadecimale preceduto da 0x, come fa %p.
 *
 * @param ptr Indirizzo da stampare. Puo' essere NULL.
 * @param base Stringa con le sedici cifre esadecimali.
 * @return int Il numero di caratteri stampati; 5 se ptr e' NULL, perche' in
 *         quel caso stampa (nil).
 */
int	ft_putptr(void *ptr, char *base)
{
	size_t	n;
	int		i;
	int		arr[30];
	int		count;

	count = 0;
	if (!ptr)
	{
		ft_putstr("(nil)");
		return (5);
	}
	n = (size_t)ptr;
	if (n == 0)
	{
		ft_putchar('0');
		return (1);
	}
	count += ft_putstr("0x");
	i = 0;
	while (n > 0)
	{
		arr[i++] = n % 16;
		n /= 16;
	}
	return (count + ft_stampina(i, base, arr));
}

/* ----- src/ft_printf/ft_putstr.c ----- */

/**
 * @brief Stampa una stringa su standard output.
 *
 * @param s Stringa da stampare. Puo' essere NULL.
 * @return int I caratteri stampati; 6 se s e' NULL, perche' in quel caso stampa
 *         (null).
 */
int	ft_putstr(char *s)
{
	if (s == NULL)
	{
		write(1, "(null)", 6);
		return (6);
	}
	write(1, s, ft_strlen(s));
	return (ft_strlen(s));
}

/* ----- src/get_next_line/get_next_line.c ----- */

/**
 * @brief Toglie dal buffer di lettura la riga gia' consegnata al chiamante.
 *
 * @param fcontent Buffer di lettura. Puo' essere NULL.
 * @return char * Il resto del buffer in una nuova stringa, NULL se non era
 *         rimasto altro; il buffer vecchio viene liberato.
 */
char	*ft_freecontent(char *fcontent)
{
	char	*tmp;
	int		start;
	int		size;

	start = 0;
	if (fcontent == NULL)
		return (NULL);
	while (fcontent[start] != '\n' && fcontent[start] != '\0')
		start++;
	if (fcontent[start] == '\0')
	{
		free (fcontent);
		return (NULL);
	}
	size = start + 1;
	while (fcontent[size] != '\0')
		size++;
	tmp = ft_calloc(size - start + 1, sizeof(char));
	if (tmp == NULL)
		return (NULL);
	size = 0;
	while (fcontent[start + 1] != '\0')
		tmp[size++] = fcontent[(start++) + 1];
	free(fcontent);
	return (tmp);
}

/**
 * @brief Copia in una nuova stringa la prima riga del buffer di lettura.
 *
 * @param fcontent Buffer di lettura. Puo' essere NULL.
 * @return char * La riga allocata, a capo finale compreso se c'e'; NULL se il
 *         buffer e' vuoto o NULL.
 */
char	*ft_extractline(char *fcontent)
{
	char	*line;
	int		start;
	int		i;

	i = 0;
	start = 0;
	if (fcontent == NULL || fcontent[0] == '\0')
		return (NULL);
	while (fcontent[start] != '\n' && fcontent[start] != '\0')
		start++;
	line = ft_calloc(start + 1 + (fcontent[start] == '\n'), sizeof(char));
	if (line == NULL)
		return (NULL);
	if (fcontent[start] == '\n')
		start++;
	while (i < start && fcontent[i] != '\0')
	{
		line[i] = fcontent[i];
		i++;
	}
	return (line);
}

/**
 * @brief Legge dal file finche' non trova un a capo o la fine.
 *
 * Legge a blocchi di BUFFER_SIZE byte e accoda quello che trova al buffer di
 * lettura.
 *
 * @param fd Descrittore aperto in lettura.
 * @param buffer Area di appoggio grande BUFFER_SIZE + 1 byte.
 * @param fcontent Buffer di lettura da estendere; puo' essere NULL la prima
 *        volta.
 * @return char * Il buffer di lettura aggiornato, NULL se la read fallisce.
 */
char	*ft_readline(int fd, char *buffer, char *fcontent)
{
	int		bytes_read;
	char	*tmp;

	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (NULL);
		if (bytes_read == 0)
			break ;
		buffer[bytes_read] = '\0';
		if (!fcontent)
			fcontent = ft_calloc(2, sizeof(char));
		tmp = fcontent;
		fcontent = ft_strjoin(tmp, buffer);
		free(tmp);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (fcontent);
}

/**
 * @brief Restituisce la riga successiva di un file, a capo finale compreso.
 *
 * Quello che viene letto oltre la riga resta conservato in un array statico
 * indicizzato dal descrittore, quindi piu' file possono essere letti
 * contemporaneamente senza che le letture si mescolino. Richiede BUFFER_SIZE
 * maggiore di zero.
 *
 * @param fd Descrittore aperto in lettura, minore di 4096.
 * @return char * La riga allocata, da liberare con free; NULL a fine file, se
 *         fd non e' valido o in caso di errore.
 */
char	*get_next_line(int fd)
{
	static char	*fcontent[4096];
	char		*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = (char *)ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer)
		return (NULL);
	if (ft_strchr(fcontent[fd], '\n') == NULL)
		fcontent[fd] = ft_readline(fd, buffer, fcontent[fd]);
	free(buffer);
	line = ft_extractline(fcontent[fd]);
	if (!line)
	{
		free(fcontent[fd]);
		fcontent[fd] = NULL;
		return (NULL);
	}
	fcontent[fd] = ft_freecontent(fcontent[fd]);
	return (line);
}

/* ----- src/get_next_line/get_next_line_utils.c ----- */

/**
 * @brief Alloca un blocco di memoria gia' azzerato.
 *
 * Se nmemb o size valgono 0 il risultato e' quello di malloc(0).
 *
 * @param nmemb Numero di elementi.
 * @param size Dimensione in byte di un elemento.
 * @return void * L'area azzerata, da liberare con free; NULL se l'allocazione
 *         fallisce o se il prodotto supera 4294967295 byte.
 */
void	*ft_calloc(size_t nmemb, size_t size)
{
	void			*tmp;
	unsigned char	*zerotmp;
	long long		result;
	int				i;

	if (nmemb == 0 || size == 0)
		return (malloc(0));
	result = (long long)nmemb * (long long)size;
	if (result > 4294967295)
		return (NULL);
	tmp = (void *)malloc(nmemb * size);
	if (tmp == NULL)
		return (NULL);
	zerotmp = (unsigned char *)tmp;
	i = 0;
	while (i < result)
		zerotmp[i++] = '\0';
	return (tmp);
}

/**
 * @brief Cerca la prima occorrenza di un carattere in una stringa.
 *
 * Il terminatore fa parte della stringa, quindi cercare '\0' trova la fine.
 *
 * @param s Stringa in cui cercare. Puo' essere NULL.
 * @param c Carattere da cercare, confrontato come unsigned char.
 * @return char * L'indirizzo dell'occorrenza, NULL se non c'e' o se s e' NULL.
 */
char	*ft_strchr(const char *s, int c)
{
	int		i;

	i = 0;
	if (s == NULL)
		return (NULL);
	while ((unsigned char)s[i] != '\0')
	{
		if ((unsigned char)s[i] == (unsigned char)c)
			return ((char *)(s + i));
		i++;
	}
	if ((unsigned char)s[i] == (unsigned char)c)
		return ((char *)s + i);
	else
		return (NULL);
}

/**
 * @brief Unisce due stringhe in una nuova.
 *
 * Le stringhe di partenza non vengono liberate.
 *
 * @param s1 Prima stringa. Puo' essere NULL: conta come stringa vuota.
 * @param s2 Seconda stringa. Puo' essere NULL: conta come stringa vuota.
 * @return char * La stringa unita, da liberare con free; NULL se l'allocazione
 *         fallisce.
 */
char	*ft_strjoin(char *s1, char *s2)
{
	size_t	i;
	size_t	l1;
	size_t	l2;
	char	*strj;

	i = 0;
	l1 = ft_strlen(s1);
	l2 = ft_strlen(s2);
	strj = ft_calloc((l1 + l2 + 1), sizeof(char));
	if (!strj)
		return (NULL);
	while (s1 && s1[i] != '\0')
	{
		strj[i] = s1[i];
		i++;
	}
	l2 = 0;
	while (s2 && s2[l2] != '\0')
	{
		strj[i + l2] = s2[l2];
		l2++;
	}
	return (strj);
}

/* ----- mega_libft.c ----- */

/**
 * @brief Da' il nome e la versione della libreria.
 *
 * @return const char * Una stringa costante, da non liberare.
 */
const char	*ft_mega_version(void)
{
	return ("mega_libft 1.0 - libft + ft_printf + get_next_line");
}

/**
 * @brief Legge una riga con get_next_line e la stampa con ft_printf.
 *
 * Mette in comunicazione il modulo get_next_line con il modulo ft_printf; la
 * riga letta viene liberata prima di restituire il risultato.
 *
 * @param fd Descrittore aperto in lettura.
 * @return int I caratteri stampati, -1 a fine file o in caso di errore.
 */
int	ft_mega_print_next_line(int fd)
{
	char	*line;
	int		count;

	line = get_next_line(fd);
	if (line == NULL)
		return (-1);
	count = ft_printf("%s", line);
	free(line);
	return (count);
}

/**
 * @brief Stampa tutto il file leggendolo riga per riga fino alla fine.
 *
 * @param fd Descrittore aperto in lettura.
 * @return int Il totale dei caratteri stampati.
 */
int	ft_mega_print_file(int fd)
{
	int	count;
	int	printed;

	count = 0;
	printed = ft_mega_print_next_line(fd);
	while (printed >= 0)
	{
		count += printed;
		printed = ft_mega_print_next_line(fd);
	}
	return (count);
}

/* ----- src/libft_bonus/ft_lstnew.c ----- */

/**
 * @brief Crea un elemento di lista che punta a un contenuto.
 *
 * @param content Dato da agganciare; viene puntato, non copiato.
 * @return t_list * Il nuovo elemento, con next a NULL; NULL se l'allocazione
 *         fallisce.
 */
t_list	*ft_lstnew(void *content)
{
	t_list	*new;

	new = (t_list *)malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->content = content;
	new->next = NULL;
	return (new);
}

/* ----- src/libft_bonus/ft_lstadd_front.c ----- */

/**
 * @brief Aggancia un elemento in testa a una lista, che diventa la nuova testa.
 *
 * @param lst Indirizzo del puntatore alla testa. Non puo' essere NULL.
 * @param new Elemento gia' creato da agganciare. Non puo' essere NULL.
 */
void	ft_lstadd_front(t_list **lst, t_list *new)
{
	new->next = *lst;
	*lst = new;
}

/* ----- src/libft_bonus/ft_lstsize.c ----- */

/**
 * @brief Conta gli elementi di una lista.
 *
 * @param lst Testa della lista.
 * @return int Il numero di elementi, 0 se la lista e' vuota.
 */
int	ft_lstsize(t_list *lst)
{
	int		i;
	t_list	*tmp;

	i = 0;
	tmp = lst;
	while (tmp != NULL)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}

/* ----- src/libft_bonus/ft_lstlast.c ----- */

/**
 * @brief Cerca l'ultimo elemento di una lista.
 *
 * @param lst Testa della lista.
 * @return t_list * L'ultimo elemento, NULL se la lista e' vuota.
 */
t_list	*ft_lstlast(t_list *lst)
{
	t_list	*tmp;

	if (lst == NULL)
		return (NULL);
	tmp = lst;
	while (tmp->next != NULL)
		tmp = tmp->next;
	return (tmp);
}

/* ----- src/libft_bonus/ft_lstadd_back.c ----- */

/**
 * @brief Aggancia un elemento in fondo a una lista.
 *
 * @param lst Indirizzo del puntatore alla testa. Se e' NULL non succede niente.
 * @param new Elemento gia' creato da agganciare. Se e' NULL non succede niente.
 */
void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (!new || !lst)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last = ft_lstlast(*lst);
	last->next = new;
}

/* ----- src/libft_bonus/ft_lstdelone.c ----- */

/**
 * @brief Libera un singolo elemento e il suo contenuto.
 *
 * Il resto della lista non viene toccato: e' il chiamante che deve aver gia'
 * ricucito i collegamenti.
 *
 * @param lst Elemento da eliminare. Se e' NULL non succede niente.
 * @param del Funzione che sa liberare il contenuto dell'elemento.
 */
void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	if (!lst)
		return ;
	del(lst->content);
	free(lst);
	lst = NULL;
}

/* ----- src/libft_bonus/ft_lstclear.c ----- */

/**
 * @brief Svuota una lista liberando contenuti ed elementi.
 *
 * Se uno dei due parametri e' NULL la funzione non fa niente.
 *
 * @param lst Indirizzo del puntatore alla testa; viene azzerato alla fine.
 * @param del Funzione che sa liberare il contenuto di un elemento.
 */
void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*tmp;
	t_list	*current;

	if (!lst || !*lst || !del)
		return ;
	current = *lst;
	while (current)
	{
		tmp = current->next;
		del(current->content);
		free(current);
		current = tmp;
	}
	*lst = NULL;
}

/* ----- src/libft_bonus/ft_lstiter.c ----- */

/**
 * @brief Applica una funzione al contenuto di ogni elemento della lista.
 *
 * @param lst Testa della lista.
 * @param f Funzione chiamata con il contenuto di ogni elemento. Non puo'
 *        essere NULL.
 */
void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*tmp;

	tmp = lst;
	while (tmp)
	{
		f(tmp->content);
		tmp = tmp->next;
	}
}

/* ----- src/libft_bonus/ft_lstmap.c ----- */

/**
 * @brief Costruisce una nuova lista trasformando il contenuto di ogni elemento.
 *
 * Se un'allocazione fallisce a meta' strada, tutto il lavoro gia' fatto viene
 * liberato prima di restituire NULL.
 *
 * @param lst Lista di partenza. Non puo' essere NULL.
 * @param f Funzione che trasforma il contenuto di un elemento.
 * @param del Funzione che sa liberare un contenuto, usata se qualcosa va
 *        storto.
 * @return t_list * La nuova lista, NULL se un parametro manca o se
 *         un'allocazione fallisce.
 */
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*list;
	t_list	*curr;
	t_list	*new;
	void	*result;

	if (lst == NULL || f == NULL || del == NULL)
		return (NULL);
	curr = lst;
	list = NULL;
	new = NULL;
	while (curr)
	{
		result = f(curr->content);
		new = ft_lstnew(result);
		if (!new)
		{
			del(result);
			ft_lstclear(&list, del);
			return (NULL);
		}
		ft_lstadd_back(&list, new);
		curr = curr->next;
	}
	return (list);
}
