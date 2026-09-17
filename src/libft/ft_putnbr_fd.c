/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwilun <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 16:08:16 by dwilun            #+#    #+#             */
/*   Updated: 2026/09/17 11:24:06 by dwilun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mega_libft.h"

/**
 * @brief Gestisce il caso limite dello zero per ft_putnbr_fd.
 *
 * Senza questo controllo il ciclo delle cifre non produrrebbe niente.
 *
 * @param n Numero gia' reso positivo dal chiamante.
 * @param fd Descrittore aperto in scrittura.
 * @return int 1 se n era 0 e lo zero e' stato scritto, 0 altrimenti.
 */
static int	ft_is_special(long n, int fd)
{
	if (n == 0)
	{
		write(fd, "0", 1);
		return (1);
	}
	return (0);
}

/**
 * @brief Scrive un intero in base 10 su un descrittore di file.
 *
 * @param n Numero da scrivere; INT_MIN e' gestito passando per un long.
 * @param fd Descrittore aperto in scrittura.
 */
void	ft_putnbr_fd(int n, int fd)
{
	int		arr[12];
	int		i;
	long	num;

	i = 0;
	num = (long)n;
	if (num < 0)
	{
		num *= -1;
		write(fd, "-", 1);
	}
	if (ft_is_special(num, fd))
	{
		return ;
	}
	while (num > 0)
	{
		arr[i++] = (num % 10) + '0';
		num /= 10;
	}
	while (--i >= 0)
	{
		write(fd, &arr[i], 1);
	}
}
