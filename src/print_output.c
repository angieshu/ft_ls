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
		printf("\n%s:\n", list->content);
		print_list(list->content, opt);
		list = list->next;
	}
	// free(list);
}

void	print_output(t_list *list, t_opt *opt)
{
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
	(flag && !list->next) ? printf("%s:\n", list->content) : 0;
	if (!list->next)
	{
		print_list(list->content, opt);
		return ;
	}
	while (list)
	{
		(n == 0) ? 0 : printf("\n");
		printf("%s:\n", list->content);
		print_list(list->content, opt);
		list = list->next;
		n++;
	}
}

void	check_dir(char **av, int i, int ac, t_opt *opt, int flag)
{
	t_output *out;
	struct stat n;

	list_set(&out);
	while (i < ac)
	{
		stat(av[i], &n);
		if (!S_ISDIR(n.st_mode) && !S_ISBLK(n.st_mode) && !S_ISCHR(n.st_mode)
			&& !S_ISFIFO(n.st_mode) && !S_ISREG(n.st_mode) &&
			!S_ISLNK(n.st_mode) && !S_ISSOCK(n.st_mode))
			list_add(&(out->notexist), av[i], ft_strlen(av[i]));
		else if (!S_ISDIR(n.st_mode))
			list_add(&(out->notdir), av[i], ft_strlen(av[i]));
		else
			list_add(&(out->dir), av[i], ft_strlen(av[i]));
		i++;
		n.st_mode = 0;
	}
	flag = (!out->notexist && !out->notdir && out->dir) ? 0 : 1;
	flag = (!out->notdir && !out->dir && out->notexist) ? 1 : 0;
	print_output(sort_dir(out->notexist, opt), opt);
	print_output(sort_dir(out->notdir, opt), opt);
	print_output_dir(sort_dir(out->dir, opt), opt, flag);
	free_out(out);
}
