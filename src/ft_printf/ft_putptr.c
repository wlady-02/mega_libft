/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwilun <dwilun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 12:07:16 by dwilun            #+#    #+#             */
/*   Updated: 2026/09/17 11:24:06 by dwilun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mega_libft.h"

/**
 * @brief Stampa le cifre raccolte da ft_putptr, che le ha prodotte al
 *        contrario.
 *
 * @param i Quante cifre ci sono nell'array.
 * @param base Stringa con le sedici cifre esadecimali.
 * @param arr Cifre dalla meno significativa alla piu' significativa.
 * @return int Il numero di caratteri stampati.
 */
static int	ft_stampina(int i, char *base, int *arr)
{
	int	count;

	count = 0;
	while (--i >= 0)
	{
		ft_putchar(base[(int)arr[i]]);
		count++;
	}
	return (count);
}

/**
 * @brief Stampa un indirizzo in esadecimale preceduto da 0x, come fa %p.
 *
 * @param ptr Indirizzo da stampare. Puo' essere NULL.
 * @param base Stringa con le sedici cifre esadecimali.
 * @return int Il numero di caratteri stampati; 5 se ptr e' NULL, perche' in
 *         quel caso stampa (nil).
 */
int	ft_putptr(void *ptr, char *base)
{
	size_t	n;
	int		i;
	int		arr[30];
	int		count;

	count = 0;
	if (!ptr)
	{
		ft_putstr("(nil)");
		return (5);
	}
	n = (size_t)ptr;
	if (n == 0)
	{
		ft_putchar('0');
		return (1);
	}
	count += ft_putstr("0x");
	i = 0;
	while (n > 0)
	{
		arr[i++] = n % 16;
		n /= 16;
	}
	return (count + ft_stampina(i, base, arr));
}
