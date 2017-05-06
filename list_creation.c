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

// t_dlist	*list_new(char *name)
// {
// 	t_dlist			*list;

// 	list = (t_dlist*)ft_memalloc(sizeof(t_dlist));
// 	list->name = name;
// 	list->next = NULL;
// 	return (list);
// }

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

