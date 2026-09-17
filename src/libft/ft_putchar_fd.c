/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwilun <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 14:31:23 by dwilun            #+#    #+#             */
/*   Updated: 2026/09/17 11:24:06 by dwilun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mega_libft.h"

/**
 * @brief Scrive un carattere su un descrittore di file.
 *
 * @param c Carattere da scrivere.
 * @param fd Descrittore aperto in scrittura.
 */
void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
