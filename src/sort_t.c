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

int		nano_sec(char *dir, char *content, t_opt *opt)
{
	struct stat	s;
	char		path_name[PATH_MAX + 1];

	lstat(path(path_name, dir, content), &s);
	return (opt->u) ? (s.st_atimespec.tv_nsec) : (s.st_mtimespec.tv_nsec);
}

t_list	*merge_list_t(char *d, t_list *a, t_list *b, t_opt *opt)
{
	t_list		tmp;
	t_list		*head;
	t_list		*c;
	int			k;

	head = &tmp;
	c = head;
	while (a && b)
	{
		if (!(k = b->content_size - a->content_size))
		{
			if (!(k = nano_sec(d, b->content, opt) -
							nano_sec(d, a->content, opt)))
				k = ft_strcmp(a->content, b->content);
		}
		c->next = (k < 0) ? a : b;
		c = (k < 0) ? a : b;
		(k < 0) ? (a = a->next) : 0;
		(k < 0) ? 0 : (b = b->next);
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
	return (merge_list_t(d, sort_t(d, a, opt), sort_t(d, b, opt), opt));
}
