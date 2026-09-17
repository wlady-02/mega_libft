/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwilun <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 13:52:54 by dwilun            #+#    #+#             */
/*   Updated: 2026/09/17 11:24:06 by dwilun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mega_libft.h"

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
