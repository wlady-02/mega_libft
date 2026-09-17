/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwilun <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 14:29:08 by dwilun            #+#    #+#             */
/*   Updated: 2026/09/17 11:24:06 by dwilun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mega_libft.h"

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
