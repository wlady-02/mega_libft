/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwilun <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 10:28:04 by dwilun            #+#    #+#             */
/*   Updated: 2026/09/17 11:24:06 by dwilun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mega_libft.h"

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
