/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwilun <dwilun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 11:22:46 by dwilun            #+#    #+#             */
/*   Updated: 2026/09/17 11:24:06 by dwilun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mega_libft.h"

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
