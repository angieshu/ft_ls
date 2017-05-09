
#include "ft_ls.h" 

void	opt_reset(t_opt *opt)
{
	opt->l = 0;
	opt->a = 0;
	opt->r = 0;
	opt->t = 0;
	opt->f = 0;
	opt->u = 0;
	opt->g = 0;
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
			&& *s != 'T' && *s != 'f' && *s != 'u' && *s != 'g')
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
		opt->g = (*s == 'g') ? 1 : opt->g;
		opt->rr = (*s == 'R') ? 1 : opt->rr;
		opt->tt = (*s == 'T') ? 1 : opt->tt;
		++s;
	}
	return (1);
}

void	time_s(time_t tim, t_opt *opt, char *content)
{
	time_t curr_time;
	struct tm *t;

	time(&curr_time);
	t = localtime(&tim);
	(t->tm_mon == 0) ? printf("Jan %2d ", t->tm_mday) : 0;
	(t->tm_mon == 1) ? printf("Feb %2d ", t->tm_mday) : 0;
	(t->tm_mon == 2) ? printf("Mar %2d ", t->tm_mday) : 0;
	(t->tm_mon == 3) ? printf("Apr %2d ", t->tm_mday) : 0;
	(t->tm_mon == 4) ? printf("May %2d ", t->tm_mday) : 0;
	(t->tm_mon == 5) ? printf("Jun %2d ", t->tm_mday) : 0;
	(t->tm_mon == 6) ? printf("Jul %2d ", t->tm_mday) : 0;
	(t->tm_mon == 7) ? printf("Aug %2d ", t->tm_mday) : 0;
	(t->tm_mon == 8) ? printf("Sep %2d ", t->tm_mday) : 0;
	(t->tm_mon == 9) ? printf("Oct %2d ", t->tm_mday) : 0;
	(t->tm_mon == 10) ? printf("Nov %2d ", t->tm_mday) : 0;
	(t->tm_mon == 11) ? printf("Dec %2d ", t->tm_mday) : 0;
	if (localtime(&curr_time)->tm_year < localtime(&tim)->tm_year)
		(opt->tt) ? printf("    %d", t->tm_year) : printf(" %d\n", t->tm_year);
	else
		printf("%02d:%02d", t->tm_hour, t->tm_min);
	(opt->tt) ? printf(":%02d", t->tm_sec) : 0;
	printf(" %s", content);

}

void	permitions(char *perm, int len)
{
	int i;

	i = 4;
	while (--i > 0)
	{
		(perm[len - i] == '0') ? printf("---") : 0; 
		(perm[len - i] == '1') ? printf("--x") : 0; 
		(perm[len - i] == '2') ? printf("-w-") : 0; 
		(perm[len - i] == '3') ? printf("-wx") : 0; 
		(perm[len - i] == '4') ? printf("r--") : 0; 
		(perm[len - i] == '5') ? printf("r-x") : 0; 
		(perm[len - i] == '6') ? printf("rw-") : 0; 
		(perm[len - i] == '7') ? printf("rwx") : 0; 
	}
	free(perm);
}

void	attrib(char *file)
{
	acl_t acl;
    acl_entry_t entry;
    ssize_t xattr = 0;

    acl = acl_get_link_np(file, ACL_TYPE_EXTENDED);
    if (acl && acl_get_entry(acl, ACL_FIRST_ENTRY, &entry) == -1)
    {
        acl_free(acl);
        acl = NULL;
    }
    xattr = listxattr(file, NULL, 0, XATTR_NOFOLLOW);
    if (xattr > 0)
        printf("@ ");
    else if (acl != NULL)
        printf("+ ");
    else
        printf("  ");
}

void	link_l(int st_nlink, int len)
{
	int diff;
	char *tmp;

	tmp = ft_itoa_base(st_nlink, 10);
	diff = len - ft_strlen(tmp);
	while (diff-- > 0)
		printf(" ");
	printf("%d ", st_nlink);
	free(tmp);
}

void	mode(mode_t st_mode, char *file, int st_nlink, int len)
{
	char *perm;
	char *attr;

	(S_ISREG(st_mode)) ? printf("-") : 0;
	(S_ISDIR(st_mode)) ? printf("d") : 0;
	(S_ISBLK(st_mode)) ? printf("b") : 0;
	(S_ISCHR(st_mode)) ? printf("c") : 0;
	(S_ISLNK(st_mode)) ? printf("l") : 0;
	(S_ISSOCK(st_mode)) ? printf("s") : 0;
	(S_ISFIFO(st_mode)) ? printf("p") : 0;
	perm = ft_itoa_base(st_mode, 8);
	permitions(perm, ft_strlen(perm));
	attrib(file);
	link_l(st_nlink, len);
}

void	user_id(uid_t user, int len)
{
	int diff;

	diff = len - ft_strlen(getpwuid(user)->pw_name);
	while (diff-- > 0)
		printf(" ");
	printf("%s  ", getpwuid(user)->pw_name);
}

void	size_l(intmax_t size, int len)
{
	int diff;
	char *tmp;

	tmp = ft_itoa_base(size, 10);
	diff = len - ft_strlen(tmp);
	while (diff-- > 0)
		printf(" ");
	printf("%s ", tmp);
	free(tmp);
}

void	gr_id(gid_t group, int len_gr, intmax_t size, int len_s)
{
	int diff;

	diff = len_gr - ft_strlen(getgrgid(group)->gr_name);
	printf("%s  ", getgrgid(group)->gr_name);
	while (diff-- > 0)
		printf(" ");
	size_l(size, len_s);
}

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

void	min_width(t_list *list, t_list *original, t_opt *opt, t_len l)
{
	t_list *tmp;
	struct stat i;

	tmp = list;
	while (list)
	{
		lstat(list->content, &i);
		l.lnk = (ft_countnbr(i.st_nlink, 10) > l.lnk) ?
									ft_countnbr(i.st_nlink, 10) : l.lnk;
		l.us = (ft_strlen(getpwuid(i.st_uid)->pw_name) > l.us) ?
							ft_strlen(getpwuid(i.st_uid)->pw_name) : l.us;
		l.gr = (ft_strlen(getgrgid(i.st_gid)->gr_name) > l.gr) ?
							ft_strlen(getgrgid(i.st_gid)->gr_name) : l.gr;
		l.size = (ft_countnbr(i.st_size, 10) > l.size) ?
										ft_countnbr(i.st_size, 10) :l.size;
		list = list->next;
		l.total += i.st_blocks;
	}
	printf("total %d\n",l. total);
	apply_opt(tmp, original, opt, l);
}

void	opt_set(t_len l)
{
	l.lnk = 0;
	l.us = 0;
	l.gr = 0;
	l.size = 0;
	l.total = 0;
}

void	apply_l(t_list *dir_list, char *dir, t_opt *opt)
{
	char name[PATH_MAX + 1];
	t_list *new_l;
	t_list *tmp;
	t_len l;

	tmp = dir_list;
	opt_set(l);
	path(name, dir, dir_list->content);
	new_l = ft_lstnew(name, ft_strlen(name));
	dir_list = dir_list->next;
	while (dir_list)
	{
		path(name, dir, dir_list->content);
		list_add_back(new_l, name, ft_strlen(name));
		dir_list = dir_list->next;
	}
	min_width(new_l, tmp, opt, l);
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
	char path_name[PATH_MAX + 1];

	if (!(list = read_dir(d, opt)))
		return ;
	if (opt->l == 1)
		apply_l(list, d, opt);
	while (list && !opt->l)
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
	else
	{
		while (i < ac)
			print_list(av[i++], opt);
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
