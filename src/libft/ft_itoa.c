/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwilun <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 10:03:19 by dwilun            #+#    #+#             */
/*   Updated: 2026/09/17 11:24:06 by dwilun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mega_libft.h"

/**
 * @brief Conta i caratteri necessari a scrivere un numero in base 10.
 *
 * Funzione di servizio di ft_itoa, serve a sapere quanta memoria allocare.
 *
 * @param n Numero da misurare, segno compreso.
 * @return int Il numero di caratteri, segno meno incluso; 1 se n vale 0.
 */
static int	ft_dim(long int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		i += 1;
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

/**
 * @brief Costruisce la rappresentazione decimale di un intero in una nuova
 *        stringa.
 *
 * @param n Numero da convertire, INT_MIN compreso.
 * @return char * La stringa allocata, da liberare con free; NULL se
 *         l'allocazione fallisce.
 */
char	*ft_itoa(int n)
{
	int			d;
	long int	num;
	char		*str;

	d = ft_dim(n);
	str = (char *)ft_calloc((d + 1), sizeof(char));
	if (!str)
		return (NULL);
	if (n < 0)
	{
		str[0] = '-';
		num = -(long int)n;
	}
	else
		num = (long int)n;
	if (num == 0)
		str[0] = '0';
	str[d] = '\0';
	while (num != 0)
	{
		str[d - 1] = (num % 10) + '0';
		num /= 10;
		d--;
	}
	return (str);
}
