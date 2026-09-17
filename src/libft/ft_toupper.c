/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwilun <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 09:46:29 by dwilun            #+#    #+#             */
/*   Updated: 2026/09/17 11:24:06 by dwilun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mega_libft.h"

/**
 * @brief Trasforma una lettera minuscola nella corrispondente maiuscola.
 *
 * @param c Carattere da convertire, passato come unsigned char o EOF.
 * @return int La maiuscola, oppure c invariato se non era una minuscola.
 */
int	ft_toupper(int c)
{
	if (c >= 97 && c <= 122)
		return (c - 32);
	return (c);
}
