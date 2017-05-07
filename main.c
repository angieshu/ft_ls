#include "ft_ls.h" 

void	opt_reset(t_opt *opt)
{
	opt->l = 0;
	opt->rr = 0;
	opt->a = 0;
	opt->r = 0;
	opt->t = 0;
	opt->tt = 0;
	opt->none = 1;
}

int		option(char *s, t_opt *opt)
{
	if (!ft_strcmp("--", s))
		return (1);
	opt->none = (!*(++s)) ? 1 : 0;
	while (*s)
	{
		if (*s != 'l' && *s != 'R' && *s != 'a' && *s != 'r' && *s != 't' && *s != 'T')
		{
			printf("./ft_ls: illegal option -- %c\n", *s);
			printf("usage: ./ft_ls [-Ralrt] [file ...]\n");
			return (0);	
		}
		opt->l = (*s == 'l') ? 1 : opt->l;
		opt->r = (*s == 'r') ? 1 : opt->r;
		opt->t = (*s == 't') ? 1 : opt->t;
		opt->a = (*s == 'a') ? 1 : opt->a;
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

void	apply_opt(t_list *dir_list, char *dir, t_opt *opt)
{
	struct stat		i_entry;
	char name[PATH_MAX + 1];
	char *time;

	if (opt->l != 1)
		return ; 
	while (dir_list && !opt->none && (opt->l || opt->t))
	{
		lstat(path(name, dir, dir_list->content), &i_entry);
		time = ctime(&i_entry.st_mtime);
		printf("%s\n", time_s(&time, opt));
			// printf("%s\n", ctime(&i_entry.st_mtime));
		dir_list = dir_list->next;
	}
}

t_list	*read_dir(char *d, t_opt *opt)
{
	struct dirent	*d_dir;
	struct stat		i_entry;
	char name[PATH_MAX + 1];
	t_list			*dir_list;
	DIR				*dir;


	dir_list = NULL;
	if (!(dir = opendir(d)))
		return (NULL);
	while ((d_dir = readdir(dir)))
	{
		if (!(d_dir->d_name[0] == '.' && opt->a != 1))
		{
			if (!list_add(&dir_list, d_dir->d_name, d_dir->d_namlen))
				return (NULL);
			if (opt->t == 1)
			{
				lstat(path(name, d, dir_list->content), &i_entry);
				dir_list->content_size = i_entry.st_mtime;
			}
		}
	}
	closedir(dir);
	return (sort_dir(dir_list, opt));
}

t_list	*view_dir(char *d, t_opt *opt)
{
	DIR *dir;
	struct dirent *entry;
	struct stat i_entry;
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
			lstat(path(path_name, d, entry->d_name), &i_entry);
			if (S_ISDIR(i_entry.st_mode))
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
// int main (int ac, char **av) {
//     acl_t acl = NULL;
//     acl_entry_t dummy;
//     ssize_t xattr = 0;
//     char str[10];

//     acl = acl_get_link_np(av[1], ACL_TYPE_EXTENDED);
//     if (acl && acl_get_entry(acl, ACL_FIRST_ENTRY, &dummy) == -1) {
//         acl_free(acl);
//         acl = NULL;
//     }
//     xattr = listxattr(av[1], NULL, 0, XATTR_NOFOLLOW);
//     if (xattr < 0)
//         xattr = 0;

//     str[1] = '\0';
//     if (xattr > 0)
//         str[0] = '@';
//     else if (acl != NULL)
//         str[0] = '+';
//     else
//         str[0] = ' ';

//     printf("%s\n", str);
//  }