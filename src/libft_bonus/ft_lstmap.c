/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwilun <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 09:38:47 by dwilun            #+#    #+#             */
/*   Updated: 2026/09/17 11:24:06 by dwilun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mega_libft.h"

/**
 * @brief Costruisce una nuova lista trasformando il contenuto di ogni elemento.
 *
 * Se un'allocazione fallisce a meta' strada, tutto il lavoro gia' fatto viene
 * liberato prima di restituire NULL.
 *
 * @param lst Lista di partenza. Non puo' essere NULL.
 * @param f Funzione che trasforma il contenuto di un elemento.
 * @param del Funzione che sa liberare un contenuto, usata se qualcosa va
 *        storto.
 * @return t_list * La nuova lista, NULL se un parametro manca o se
 *         un'allocazione fallisce.
 */
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*list;
	t_list	*curr;
	t_list	*new;
	void	*result;

	if (lst == NULL || f == NULL || del == NULL)
		return (NULL);
	curr = lst;
	list = NULL;
	new = NULL;
	while (curr)
	{
		result = f(curr->content);
		new = ft_lstnew(result);
		if (!new)
		{
			del(result);
			ft_lstclear(&list, del);
			return (NULL);
		}
		ft_lstadd_back(&list, new);
		curr = curr->next;
	}
	return (list);
}
