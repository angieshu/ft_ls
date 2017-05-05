/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_dir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashulha <ashulha@student.us.org>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 16:17:17 by ashulha           #+#    #+#             */
/*   Updated: 2017/05/04 16:17:18 by ashulha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h" 

t_dlist		*merge_list(t_dlist *a, t_dlist *b, t_opt *opt)
{
	t_dlist tmp;
	t_dlist *head;
	t_dlist *c;
	int k;

	head = &tmp;
	c = head;
	while (a && b)
	{
		k = ft_strcmp(a->name, b->name);
		if ((k < 0 && opt->r != 1) || (k > 0 && opt->r == 1))
		{
			c->next = a;
			c = a;
			a = a->next;
		}
		else
		{
			c->next = b;
			c = b;
			b = b->next;
		}
	}
	c->next = (a == 0) ? b : a;
	return (head->next);
}

t_dlist		*sort_dir(t_dlist *head, t_opt *opt)
{
	t_dlist *a;
	t_dlist *b;

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
	return (merge_list(sort_dir(a, opt), sort_dir(b, opt), opt));
}
