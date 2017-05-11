/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_output.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashulha <ashulha@student.us.org>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/09 14:57:14 by ashulha           #+#    #+#             */
/*   Updated: 2017/05/09 14:58:03 by ashulha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_dir(char *curr_dir, t_opt *opt)
{
	t_list	*list;

	if (!(list = view_dir(curr_dir, opt)))
		return ;
	while (list)
	{
		ft_printf("\n%s:\n", list->content);
		print_list(list->content, opt);
		list = list->next;
	}
}

void	print_output(t_list *list, t_opt *opt)
{
	if (!list->next)
	{
		print_list(list->content, opt);
		return ;
	}
	while (list)
	{
		print_list(list->content, opt);
		list = list->next;
	}
}

void	print_output_dir(t_list *list, t_opt *opt, int flag)
{
	int n;

	n = 0;

	(flag && !list->next) ? ft_printf("%s:\n", list->content) : 0;
	if (!list->next)
	{
		print_list(list->content, opt);
		return ;
	}
	while (list)
	{
		(n == 0) ? 0 : ft_printf("\n");
		ft_printf("%s:\n", list->content);
		print_list(list->content, opt);
		list = list->next;
		n++;
	}
}

int		last_check(char *name)
{
	if (!ft_strncmp("", name, PATH_MAX))
	{
		ft_printf("ft_ls: fts_open: No such file or directory\n");
		return (0);
	}
	return (1);
}

void	check_dir(char **av, int i, int ac, t_opt *opt, int flag)
{
	t_output *out;
	struct stat n;

	list_set(&out);
	while (i < ac)
	{
		stat(av[i], &n);
		(!last_check(av[i])) ? free_out(out) : 0;
		if (!last_check(av[i]))
			return ;
		if (!n.st_atime)
			list_add(&(out->notexist), av[i], ft_strlen(av[i]));
		else if (!S_ISDIR(n.st_mode))
			list_add(&(out->notdir), av[i], ft_strlen(av[i]));
		else
			list_add(&(out->dir), av[i], ft_strlen(av[i]));
		i++;
		n.st_atime = 0;
	}
	flag = (!out->notexist && !out->notdir && out->dir) ? 0 : 1;
	(out->notexist) ? print_output(sort_dir(".", out->notexist, opt), opt) : 0;
	(out->notdir) ? print_output(sort_dir(".", out->notdir, opt), opt) : 0;
	(out->dir) ? print_output_dir(sort_dir(".", out->dir, opt), opt, flag) : 0;
	free_out(out);
}
