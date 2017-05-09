
#include "ft_ls.h" 

int		option(char *s, t_opt *opt)
{
	if (!ft_strcmp("--", s))
		return (1);
	opt->none = (!*(++s)) ? 1 : 0;
	while (*s)
	{
		if (*s != 'l' && *s != 'R' && *s != 'a' && *s != 'r' && *s != 't'
			&& *s != 'T' && *s != 'f' && *s != 'u' && *s != 'g' && *s != 'd')
		{
			printf("ft_ls: illegal option -- %c\n", *s);
			printf("usage: ft_ls [-RTadfglrtu] [file ...]\n");
			return (0);	
		}
		opt->l = (*s == 'l') ? 1 : opt->l;
		opt->r = (*s == 'r') ? 1 : opt->r;
		opt->t = (*s == 't') ? 1 : opt->t;
		opt->a = (*s == 'a') ? 1 : opt->a;
		opt->f = (*s == 'f') ? 1 : opt->f;
		opt->u = (*s == 'u') ? 1 : opt->u;
		opt->g = (*s == 'g') ? 1 : opt->g;
		opt->d = (*s == 'd') ? 1 : opt->d;
 		opt->rr = (*s == 'R') ? 1 : opt->rr;
		opt->tt = (*s == 'T') ? 1 : opt->tt;
		++s;
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
			if (S_ISDIR(info.st_mode))
				if (!list_add(&list, path_name, ft_strlen(path_name)))
					return (NULL);
		}
	}
	closedir(dir);
	return (sort_dir(list, opt));
}

void	print_dir(char *curr_dir, t_opt *opt)
{
	t_list	*list;

	if (!(list = view_dir(curr_dir, opt)))
		return ;
	while (list)
	{
		printf("%s:\n", list->content);
		print_list(list->content, opt);
		list = list->next;
	}
	free(list);
}

void print_output(t_list *list, t_opt *opt)
{
	while (list)
	{
		print_list(list->content, opt);
		list = list->next;
	}
}

void	print_output_dir(t_list *list, t_opt *opt)
{
	int n;

	n = 0;
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

void	check_dir(char **av, int i, int ac, t_opt *opt)
{
	t_output *out;
	struct stat info;

	list_set(&out);
	while (i < ac)
	{
		stat(av[i], &info);
		if (!S_ISDIR(info.st_mode) && !S_ISBLK(info.st_mode) && !S_ISCHR(info.st_mode)
		&& !S_ISFIFO(info.st_mode) && !S_ISREG(info.st_mode) &&
		!S_ISLNK(info.st_mode) && !S_ISSOCK(info.st_mode))
			list_add(&(out->notexist), av[i], ft_strlen(av[i]));
		else if (!S_ISDIR(info.st_mode))
			list_add(&(out->notdir), av[i], ft_strlen(av[i]));
		else
			list_add(&(out->dir), av[i], ft_strlen(av[i]));
		i++;
		info.st_mode = 0;
	}
	print_output(sort_dir(out->notexist, opt), opt);
	print_output(sort_dir(out->notdir, opt), opt);
	print_output_dir(sort_dir(out->dir, opt), opt);

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
	(opt->l == 1) ? apply_l(list, d, opt) : 0;
	while (list && !opt->l)
	{
		printf("%s\n", list->content);
		list = list->next;
	}
	//free(list);
	(opt->rr == 1) ? print_dir(d, opt) : 0;
}


int		main(int ac, char **av)
{
	int i;
	t_opt opt;

	i = 1;
	opt_reset(&opt);
	if (ac > 1 && av[1][0] == '-')
	{
		if (!option(av[1], &opt))
			return (0);
		i++;
	}
	(i == ac) ? print_list(".", &opt) : check_dir(av, i, ac, &opt);
}
