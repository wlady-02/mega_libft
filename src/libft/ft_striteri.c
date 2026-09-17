/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwilun <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 14:24:45 by dwilun            #+#    #+#             */
/*   Updated: 2026/09/17 11:24:06 by dwilun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mega_libft.h"

/**
 * @brief Applica una funzione a ogni carattere di una stringa, sul posto.
 *
 * @param s Stringa da percorrere. Non puo' essere NULL.
 * @param f Funzione chiamata con l'indice e l'indirizzo del carattere, cosi'
 *        puo' modificarlo.
 */
void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		f(i, &s[i]);
		i++;
	}
	s[i] = '\0';
}
