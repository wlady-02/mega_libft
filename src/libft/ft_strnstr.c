/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwilun <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 12:10:30 by dwilun            #+#    #+#             */
/*   Updated: 2026/09/17 11:24:06 by dwilun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mega_libft.h"

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
