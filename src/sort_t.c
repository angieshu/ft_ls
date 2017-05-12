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

t_list	*merge_list_t_mod(char *d, t_list *a, t_list *b)
{
	t_list		tmp;
	t_list		*head;
	t_list		*c;
	t_stat		s;
	char		path_name[PATH_MAX + 1];

	head = &tmp;
	c = head;
	while (a && b)
	{
		lstat(path(path_name, d, a->content), s.ia);
		lstat(path(path_name, d, b->content), s.ib);
		if (!(s.k = b->content_size - a->content_size))
		{
			if (!(s.k = s.ib->st_mtimespec.tv_nsec -
							s.ia->st_mtimespec.tv_nsec))
				s.k = ft_strcmp(a->content, b->content);
		}
		c->next = (s.k < 0) ? a : b;
		c = (s.k < 0) ? a : b;
		(s.k < 0) ? (a = a->next) : 0;
		(s.k < 0) ? 0 : (b = b->next);
	}
	c->next = (a == 0) ? b : a;
	return (head->next);
}

t_list	*merge_list_t_acc(char *d, t_list *a, t_list *b)
{
	t_list		tmp;
	t_list		*head;
	t_list		*c;
	t_stat		s;
	char		path_name[PATH_MAX + 1];

	head = &tmp;
	c = head;
	while (a && b)
	{
		lstat(path(path_name, d, a->content), s.ia);
		lstat(path(path_name, d, b->content), s.ib);
		if (!(s.k = b->content_size - a->content_size))
		{
			if (!(s.k = s.ib->st_atimespec.tv_nsec -
							s.ia->st_atimespec.tv_nsec))
				s.k = ft_strcmp(a->content, b->content);
		}
		c->next = (s.k < 0) ? a : b;
		c = (s.k < 0) ? a : b;
		(s.k < 0) ? (a = a->next) : 0;
		(s.k < 0) ? 0 : (b = b->next);
	}
	c->next = (a == 0) ? b : a;
	return (head->next);
}

t_list	*sort_t(char *d, t_list *head, t_opt *opt)
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
	return (opt->u) ?
	(merge_list_t_acc(d, sort_t(d, a, opt), sort_t(d, b, opt)))
	: (merge_list_t_mod(d, sort_t(d, a, opt), sort_t(d, b, opt)));
}
