#include "ft_ls.h" 

void	opt_reset(t_opt *opt)
{
	opt->l = 0;
	opt->a = 0;
	opt->r = 0;
	opt->t = 0;
	opt->f = 0;
	opt->u = 0;
	opt->rr = 0;
	opt->tt = 0;
	opt->none = 0;
}

int		option(char *s, t_opt *opt)
{
	if (!ft_strcmp("--", s))
		return (1);
	opt->none = (!*(++s)) ? 1 : 0;
	while (*s)
	{
		if (*s != 'l' && *s != 'R' && *s != 'a' && *s != 'r' && *s != 't'
			&& *s != 'T' && *s != 'f' && *s != 'u')
		{
			printf("./ft_ls: illegal option -- %c\n", *s);
			printf("usage: ./ft_ls [-Ralrt] [file ...]\n");
			return (0);	
		}
		opt->l = (*s == 'l') ? 1 : opt->l;
		opt->r = (*s == 'r') ? 1 : opt->r;
		opt->t = (*s == 't') ? 1 : opt->t;
		opt->a = (*s == 'a') ? 1 : opt->a;
		opt->f = (*s == 'f') ? 1 : opt->f;
		opt->u = (*s == 'u') ? 1 : opt->u;
		opt->rr = (*s == 'R') ? 1 : opt->rr;
		opt->tt = (*s == 'T') ? 1 : opt->tt;
		++s;
	}
	return (1);
}

char	*time_s(char **time, t_opt *opt)
{
	char *s;
	int i;
	int n;

	i = 0;
	n = 0;
	s = (opt->tt == 1) ? ft_strnew(20) : ft_strnew(17);
	while (**time != ' ')
		(*time)++;
	(*time)++;
	while (**time != '\n')
	{
		n += (**time == ':') ? 1 : 0;
		if (**time == ':' && n > 0 && opt->tt != 1)
			(*time) += 3;
		s[i++] = **time;
		(*time)++;
	}
	return (s);
}

char	*permitions(char *perm)
{
	int i;
	int len;
	char *s;

	i = 4;
	s = ft_strnew(9);
	len = ft_strlen(perm);
	while (--i > 0)
	{
		if (perm[len - i] == '0')
			ft_strncat(s, "---", PATH_MAX);
		else if (perm[len - i] == '1')
			ft_strncat(s, "--x", PATH_MAX);
		else if (perm[len - i] == '2')
			ft_strncat(s, "-w-", PATH_MAX);
		else if (perm[len - i] == '3')
			ft_strncat(s, "-wx", PATH_MAX);
		else if (perm[len - i] == '4')
			ft_strncat(s, "r--", PATH_MAX);
		else if (perm[len - i] == '5')
			ft_strncat(s, "r-x", PATH_MAX);
		else if (perm[len - i] == '6')
			ft_strncat(s, "rw-", PATH_MAX);
		else if (perm[len - i] == '7')
			ft_strncat(s, "rwx", PATH_MAX);
	}
	return (s);
}

char	*mode(mode_t st_mode)
{
	char *s;

	s = ft_strnew(1);
	if (S_ISBLK(st_mode))
		s[0] = 'b';
	else if (S_ISCHR(st_mode))
		s[0] = 'c';
	else if (S_ISDIR(st_mode))
		s[0] = 'd';
	else if (S_ISLNK(st_mode))
		s[0] = 'l';
	else if (S_ISSOCK(st_mode))
		s[0] = 's';
	else if (S_ISFIFO(st_mode))
		s[0] = 'p';
	else
		s[0] = '-';
	return (s);
}

char	*attrib(char *file)
{
	acl_t acl;
    acl_entry_t entry;
    ssize_t xattr = 0;
    char *s;

    s = ft_strnew(1);
    acl = acl_get_link_np(file, ACL_TYPE_EXTENDED);
    if (acl && acl_get_entry(acl, ACL_FIRST_ENTRY, &entry) == -1)
    {
        acl_free(acl);
        acl = NULL;
    }
    xattr = listxattr(file, NULL, 0, XATTR_NOFOLLOW);
    if (xattr > 0)
        s[0] = '@';
    else if (acl != NULL)
        s[0] = '+';
    else
        s[0] = ' ';
    return (s);
}

void	apply_opt(t_list *dir_list, char *dir, t_opt *opt)
{
	struct stat	info;
	char name[PATH_MAX + 1];
	char *time;
	int total;

	total = 0;
	while (dir_list)
	{
		lstat(path(name, dir, dir_list->content), &info);
		time = (opt->u) ? ctime(&info.st_atime) : ctime(&info.st_mtime);
		// printf("%s\n", time_s(&time, opt));
			// printf("%d\n", info.st_nlink);
		// printf("%s%s%s\n", mode(info.st_mode), permitions(ft_itoa_base(info.st_mode, 8)), attrib(name));
		total += info.st_blocks;
		dir_list = dir_list->next;
	}
	printf("total %d\n", total);
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

char	*path(char *path_name, char *curr_dir, char *file_name)
{
	ft_strncpy(path_name, curr_dir, PATH_MAX);
	ft_strncat(path_name, "/", PATH_MAX);
	ft_strncat(path_name, file_name, PATH_MAX);
	return (path_name);
}

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
	free(list);
}

void	print_list(char *d, t_opt *opt)
{
	t_list *list;

	if (!(list = read_dir(d, opt)))
		return ;
	if (opt->l == 1)
		apply_opt(list, d, opt);
	while (list)
	{
		printf("%s\n", list->content);
		list = list->next;
	}
	free(list);
	if (opt->rr == 1)
		print_dir(d, opt);
}

void	check_directory(int ac, char **av, t_opt *opt, int i)
{
	if (i == ac)
		print_list(".", opt);
		// read_dir(getenv("PWD"), opt);
	else
	{
		while (i < ac)
			print_list(av[i++], opt);
			// read_dir(av[i++], opt);
	}
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
	check_directory(ac, av, &opt, i);
}
