/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwilun <dwilun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 15:04:49 by dwilun            #+#    #+#             */
/*   Updated: 2026/09/17 16:52:40 by dwilun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mega_libft.h"

/**
 * @brief Stampa su standard output una stringa di formato con i suoi argomenti.
 *
 * Gestisce le conversioni c, s, p, d, i, u, x, X e il percento raddoppiato. Non
 * gestisce flag, ampiezza e precisione. Un percento in fondo alla stringa, a
 * cui non segue nessuna lettera, ferma la stampa: non viene stampato e il
 * conteggio restituito e' quello dei caratteri usciti fino a li'.
 *
 * @param str Stringa di formato, seguita dagli argomenti richiesti dalle
 *        conversioni.
 * @return int Il numero di caratteri stampati, 0 se il formato e' NULL o vuoto.
 */
int	ft_printf(const char *str, ...)
{
	va_list	argl;
	int		i;
	int		count;

	i = 0;
	count = 0;
	if (!str || !*str)
		return (0);
	va_start(argl, str);
	while (str[i] != '\0')
	{
		if (str[i] == '%' && str[i + 1] == '\0')
			break ;
		if (str[i] == '%')
			count += ft_conv_printf(&argl, str[++i]);
		else
		{
			ft_putchar(str[i]);
			count++;
		}
		i++;
	}
	va_end(argl);
	return (count);
}
