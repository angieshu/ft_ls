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
	if ((tmp = ft_lstnew(name,size)))
		head->next = tmp;
}

void	free_list(t_list **list)
{
	t_list *tmp;

	tmp = *list;
	while (tmp)
	{
		free(tmp->content);
		tmp = tmp->next;
	}
	free(*list);
}

void	free_out(t_output *out)
{
	free_list(&out->notexist);
	free_list(&out->notdir);
	free_list(&out->dir);
	free(out);
}