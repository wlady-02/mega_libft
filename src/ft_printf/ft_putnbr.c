/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwilun <dwilun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 16:08:16 by dwilun            #+#    #+#             */
/*   Updated: 2026/09/17 11:24:06 by dwilun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mega_libft.h"

/**
 * @brief Stampa un intero in base 10 su standard output.
 *
 * @param n Numero da stampare; INT_MIN e' gestito passando per un long.
 * @return int Il numero di caratteri stampati, segno meno compreso.
 */
int	ft_putnbr(int n)
{
	int		count;
	long	num;

	count = 0;
	num = (long)n;
	if (num < 0)
	{
		num *= -1;
		ft_putchar('-');
		count++;
	}
	if (num >= 10)
	{
		count += ft_putnbr(num / 10);
		num %= 10;
	}
	if (num < 10)
	{
		ft_putchar(num + '0');
		count++;
	}
	return (count);
}
