/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashulha <ashulha@student.us.org>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/09 15:54:00 by ashulha           #+#    #+#             */
/*   Updated: 2017/05/09 15:54:03 by ashulha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "ft_ls.h" 

int		option(char **s, t_opt *opt)
{
	if (!ft_strcmp("--", *s))
		return (1);
	opt->none = (!++(*s)) ? 1 : 0;
	while (**s)
	{
		if (**s != 'l' && **s != 'R' && **s != 'a' && **s != 'r' && **s != 't'
			&& **s != 'T' && **s != 'f' && **s != 'u' && **s != 'g' && **s != 'd')
		{
			printf("ft_ls: illegal option -- %c\n", **s);
			printf("usage: ft_ls [-RTadfglrtu] [file ...]\n");
			return (0);	
		}
		opt->l = (**s == 'l') ? 1 : opt->l;
		opt->r = (**s == 'r') ? 1 : opt->r;
		opt->t = (**s == 't') ? 1 : opt->t;
		opt->a = (**s == 'a') ? 1 : opt->a;
		opt->f = (**s == 'f') ? 1 : opt->f;
		opt->u = (**s == 'u') ? 1 : opt->u;
		opt->g = (**s == 'g') ? 1 : opt->g;
		opt->d = (**s == 'd') ? 1 : opt->d;
 		opt->rr = (**s == 'R') ? 1 : opt->rr;
		opt->tt = (**s == 'T') ? 1 : opt->tt;
		++(*s);
	}
	return (1);
}

t_list	*read_dir(char *d, t_opt *opt)
{
	struct dirent	*d_dir;
	struct stat		info;
	char name[PATH_MAX + 1];
	t_list			*dir_list;
	DIR				*dir;


	dir_list = NULL;
	if (!(dir = opendir(d)))
		return (NULL);
	while ((d_dir = readdir(dir)))
	{
		if (!(d_dir->d_name[0] == '.' && !opt->a  && !opt->f))
		{
			if (!list_add(&dir_list, d_dir->d_name, d_dir->d_namlen))
				return (NULL);
			if (opt->t == 1)
			{
				lstat(path(name, d, dir_list->content), &info);
				dir_list->content_size = (opt->u) ? info.st_atime : info.st_mtime;
			}
		}
	}
	if (opt->f)
		return (listrev(dir_list));
	closedir(dir);
	return (sort_dir(dir_list, opt));
}

t_list	*view_dir(char *d, t_opt *opt)
{
	DIR *dir;
	struct dirent *entry;
	struct stat info;
	char path_name[PATH_MAX + 1];
	t_list *list;
	
	list = NULL;
	dir = opendir(d);
	while ((entry = readdir(dir)))
	{
		if (ft_strncmp(entry->d_name, ".", PATH_MAX) &&
			ft_strncmp(entry->d_name, "..", PATH_MAX) &&
			(!(entry->d_name[0] == '.' && opt->a != 1)))
		{
			lstat(path(path_name, d, entry->d_name), &info);
			list->content_size = (opt->u) ? info.st_atime : info.st_mtime;
			if (S_ISDIR(info.st_mode))
				if (!list_add(&list, path_name, ft_strlen(path_name)))
					return (NULL);
		}
	}
	closedir(dir);
	return (sort_dir(list, opt));
}

void	print_list(char *d, t_opt *opt)
{
	t_list *list;
	struct stat i;

	lstat(d, &i);
	if (!S_ISDIR(i.st_mode) && !S_ISBLK(i.st_mode) && !S_ISCHR(i.st_mode)
		&& !S_ISFIFO(i.st_mode) && !S_ISREG(i.st_mode) &&
		!S_ISLNK(i.st_mode) && !S_ISSOCK(i.st_mode))
	{
		printf("ft_ls: %s: No such file or directory\n", d);
		return ;
	}
	(!S_ISDIR(i.st_mode) || opt->d) ? list = ft_lstnew(d, ft_strlen(d)) : 0;
	if (S_ISDIR(i.st_mode) && !(list = read_dir(d, opt)))
	{
		printf("ls: %s: Permission denied\n", d);
		return ;
	}
	(opt->l || opt->g) ? apply_l(list, d, opt) : 0;
	while (list && !opt->l && !opt->g)
	{
		printf("%s\n", list->content);
		list = list->next;
	}
	(list) ? free_list(&list) : 0;
	(opt->rr) ? print_dir(d, opt) : 0;
}


int		main(int ac, char **av)
{
	int i;
	t_opt opt;

	i = 1;
	opt_reset(&opt);
	while (i < ac && av[i][0] == '-')
	{
		if (!option(&av[i], &opt))
			return (0);
		i++;
	}
	(i == ac) ? print_list(".", &opt) : check_dir(av, i, ac, &opt, 0);
	return (0);
}

