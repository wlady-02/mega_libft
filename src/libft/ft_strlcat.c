/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwilun <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 09:24:52 by dwilun            #+#    #+#             */
/*   Updated: 2026/09/17 11:24:06 by dwilun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mega_libft.h"

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
