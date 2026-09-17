/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_b.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwilun <dwilun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 09:15:12 by dwilun            #+#    #+#             */
/*   Updated: 2026/09/17 11:24:06 by dwilun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mega_libft.h"

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
