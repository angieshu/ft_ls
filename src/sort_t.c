/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_t.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashulha <ashulha@student.us.org>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/10 14:00:15 by ashulha           #+#    #+#             */
/*   Updated: 2017/05/10 14:00:16 by ashulha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_list		*merge_list_t(t_list *a, t_list *b, intmax_t k)
{
	t_list tmp;
	t_list *head;
	t_list *c;

	head = &tmp;
	c = head;
	while (a && b)
	{
		if (!(k = b->content_size - a->content_size))
			k = ft_strcmp(a->content, b->content);
			c->next = (k < 0) ? a : b;
			c = (k < 0) ? a : b;
			(k < 0) ? (a = a->next) : (b = b->next);
	}
	c->next = (a == 0) ? b : a;
	return (head->next);
}

t_list	*sort_t(t_list *head)
{
	t_list *a;
	t_list *b;

	if (!head || !head->next)
		return (head);
	a = head;
	b = head->next;
	while (b && b->next)
	{
		head = head->next;
		b = b->next->next;
	}
	b = head->next;
	head->next = 0;
	return (merge_list_t(sort_t(a), sort_t(b), 0));

}

