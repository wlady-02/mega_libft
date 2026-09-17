/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mega_libft.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwilun <dwilun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/16 00:00:00 by dwilun            #+#    #+#             */
/*   Updated: 2026/09/17 11:24:06 by dwilun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mega_libft.h"

/**
 * @brief Da' il nome e la versione della libreria.
 *
 * @return const char * Una stringa costante, da non liberare.
 */
const char	*ft_mega_version(void)
{
	return ("mega_libft 1.0 - libft + ft_printf + get_next_line");
}

/**
 * @brief Legge una riga con get_next_line e la stampa con ft_printf.
 *
 * Mette in comunicazione il modulo get_next_line con il modulo ft_printf; la
 * riga letta viene liberata prima di restituire il risultato.
 *
 * @param fd Descrittore aperto in lettura.
 * @return int I caratteri stampati, -1 a fine file o in caso di errore.
 */
int	ft_mega_print_next_line(int fd)
{
	char	*line;
	int		count;

	line = get_next_line(fd);
	if (line == NULL)
		return (-1);
	count = ft_printf("%s", line);
	free(line);
	return (count);
}

/**
 * @brief Stampa tutto il file leggendolo riga per riga fino alla fine.
 *
 * @param fd Descrittore aperto in lettura.
 * @return int Il totale dei caratteri stampati.
 */
int	ft_mega_print_file(int fd)
{
	int	count;
	int	printed;

	count = 0;
	printed = ft_mega_print_next_line(fd);
	while (printed >= 0)
	{
		count += printed;
		printed = ft_mega_print_next_line(fd);
	}
	return (count);
}
