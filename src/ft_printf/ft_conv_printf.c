/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conv_printf.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwilun <dwilun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 11:31:23 by dwilun            #+#    #+#             */
/*   Updated: 2026/09/17 11:24:06 by dwilun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mega_libft.h"

/**
 * @brief Esegue una singola conversione di ft_printf.
 *
 * Riconosce c, s, p, d, i, u, x, X e il percento raddoppiato.
 *
 * @param argl Elenco degli argomenti variabili, passato per indirizzo perche'
 *        la funzione lo fa avanzare.
 * @param c Lettera che segue il segno di percento.
 * @return int I caratteri stampati, 0 se la conversione non e' riconosciuta.
 */
int	ft_conv_printf(va_list *argl, int c)
{
	int	i;

	if (c == 'c')
		i = ft_putchar((int)va_arg(*argl, int));
	else if (c == 's')
		i = ft_putstr(va_arg(*argl, char *));
	else if (c == 'p')
		i = ft_putptr(va_arg(*argl, void *), "0123456789abcdef");
	else if (c == 'd' || c == 'i')
		i = ft_putnbr(va_arg(*argl, int));
	else if (c == 'u')
		i = ft_putnbr_b((unsigned int)va_arg(*argl, unsigned int),
				"0123456789", 10);
	else if (c == 'x')
		i = ft_putnbr_b((unsigned int)va_arg(*argl, unsigned int),
				"0123456789abcdef", 16);
	else if (c == 'X')
		i = ft_putnbr_b((unsigned int)va_arg(*argl, unsigned int),
				"0123456789ABCDEF", 16);
	else if (c == '%')
		i = ft_putchar('%');
	else
		return (0);
	return (i);
}
