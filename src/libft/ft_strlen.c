/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwilun <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 12:56:50 by dwilun            #+#    #+#             */
/*   Updated: 2026/09/17 11:24:06 by dwilun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mega_libft.h"

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
