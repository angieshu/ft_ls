/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_creation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashulha <ashulha@student.us.org>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/05 16:50:15 by ashulha           #+#    #+#             */
/*   Updated: 2017/05/05 16:50:16 by ashulha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		list_add(t_list **head, char *name, size_t size)
{
	t_list			*tmp;

	if ((tmp = ft_lstnew(name, size)))
	{
		tmp->next = *head;
		*head = tmp;
		return (1);
	}
	free(tmp);
	return (0);
}

void	list_add_back(t_list *head, char *name, size_t size)
{
	t_list			*tmp;

	while (head->next)
		head = head->next;
	if ((tmp = ft_lstnew(name, size)))
		head->next = tmp;
}

char	*get_elem_n(t_list *list, int elem_n)
{
	while (list && elem_n-- > 0)
		list = list->next;
	if (!list || elem_n > 0)
		return (NULL);
	return (list->content);
}

void	free_list(t_list **list)
{
	t_list *tmp;

	tmp = *list;
	while (tmp)
	{
		(tmp->content) ? free(tmp->content) : 0;
		tmp = tmp->next;
	}
	(list) ? free(*list) : 0;
}

void	free_out(t_output *out)
{
	(out->notexist) ? free_list(&out->notexist) : 0;
	(out->notdir) ? free_list(&out->notdir) : 0;
	(out->dir) ? free_list(&out->dir) : 0;
	free(out);
}
