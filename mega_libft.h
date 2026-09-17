/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mega_libft.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwilun <dwilun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/16 00:00:00 by dwilun            #+#    #+#             */
/*   Updated: 2026/09/17 16:52:40 by dwilun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MEGA_LIBFT_H
# define MEGA_LIBFT_H

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

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 3
# endif

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <stdarg.h>
# include <stdio.h>
# include <fcntl.h>

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

#endif
