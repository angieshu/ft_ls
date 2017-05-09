/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_opt_l.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashulha <ashulha@student.us.org>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/09 14:42:44 by ashulha           #+#    #+#             */
/*   Updated: 2017/05/09 14:42:45 by ashulha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	apply_opt(t_list *list, t_list *original, t_opt *opt, t_len l)
{
	struct stat i;
	char lnk_s[PATH_MAX + 1];

	while (list)
	{
		lstat(list->content, &i);
		mode(i.st_mode, list->content, i.st_nlink, l.lnk);
		if (!opt->g)
			user_id(i.st_uid, l.us);
		gr_id(i.st_gid, l.gr, i.st_size, l.size);
		time_s((opt->u) ? i.st_atime : i.st_mtime, opt, original->content);
		if (S_ISLNK(i.st_mode))
			(readlink(list->content, lnk_s, PATH_MAX) != 1) ?
			printf(" -> %s", lnk_s) : printf(" -> (invalid symbolic link!)");
		printf("\n");
		list = list->next;
		original = original->next; 
	}
}

void	min_width(t_list *list, t_list *original, t_opt *opt, t_len *l)
{
	t_list *tmp;
	struct stat i;

	if (!list->next)
	{
		apply_opt(list, original, opt, *l);
		return ;
	}
	tmp = list;
	while (list)
	{
		lstat(list->content, &i);
		l->lnk = (ft_countnbr(i.st_nlink, 10) > l->lnk) ?
									ft_countnbr(i.st_nlink, 10) : l->lnk;
		l->us = (ft_strlen(getpwuid(i.st_uid)->pw_name) > l->us) ?
							ft_strlen(getpwuid(i.st_uid)->pw_name) : l->us;
		l->gr = (ft_strlen(getgrgid(i.st_gid)->gr_name) > l->gr) ?
							ft_strlen(getgrgid(i.st_gid)->gr_name) : l->gr;
		l->size = (ft_countnbr(i.st_size, 10) > l->size) ?
										ft_countnbr(i.st_size, 10) :l->size;
		list = list->next;
		l->total += i.st_blocks;
	}
	printf("total %d\n", l->total);
	apply_opt(tmp, original, opt, *l);
}

void	apply_l(t_list *dir_list, char *dir, t_opt *opt)
{
	char name[PATH_MAX + 1];
	t_list *new_l;
	t_list *tmp;
	t_len l;

	opt_set(&l);
	if (!dir_list->next)
	{
		min_width(dir_list, dir_list, opt, &l);
		return ;
	}
	tmp = dir_list;
	path(name, dir, dir_list->content);
	new_l = ft_lstnew(name, ft_strlen(name));
	dir_list = dir_list->next;
	while (dir_list)
	{
		path(name, dir, dir_list->content);
		list_add_back(new_l, name, ft_strlen(name));
		dir_list = dir_list->next;
	}
	min_width(new_l, tmp, opt, &l);
}
