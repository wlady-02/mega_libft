/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwilun <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 10:22:31 by dwilun            #+#    #+#             */
/*   Updated: 2026/09/17 11:24:06 by dwilun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mega_libft.h"

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
