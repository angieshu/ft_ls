#include "ft_ls.h" 

void	opt_reset(t_opt *opt)
{
	opt->l = 0;
	opt->rr = 0;
	opt->a = 0;
	opt->r = 0;
	opt->t = 0;
	opt->none = 1;
}

int		option(char *s, t_opt *opt)
{
	opt->none = (!*(++s)) ? 1 : 0;
	while (*s)
	{
		if (*s == 'l')
			opt->l = 1;
		else if (*s == 'R')
			opt->rr = 1;
		else if (*s == 'a')
			opt->a = 1;
		else if (*s == 'r')
			opt->r = 1;
		else if (*s == 't')
			opt->t = 1;
		else if (*s == '-' && opt->none != 1)
			opt->none = 1;
		else
		{
			printf("./ft_ls: illigal option -- %c\n", *s);
			printf("usage: ./ft_ls [-Ralrt] [file ...]\n");
			return (0);
		}
		++s;
	}
	return (1);
}

t_dlist	*read_dir(char *d, t_opt *opt)
{
	struct dirent	*d_dir;
	t_dlist			*dir_list;
	t_dlist			*dir_tmp;
	DIR				*dir;

	dir = opendir(d);
	if (!(d_dir = readdir(dir)))
		return (NULL);
	dir_list = (t_dlist*)ft_memalloc(sizeof(t_dlist));
	dir_list->name = d_dir->d_name;
	dir_list->next = NULL;
	while ((d_dir = readdir(dir)))
	{
		dir_tmp = (t_dlist*)ft_memalloc(sizeof(t_dlist));
		if (!(dir_tmp->name = d_dir->d_name))
			break ;
		dir_tmp->next = dir_list;
		dir_list = dir_tmp;
	}
	// if (dir_tmp)
	// 	free(dir_tmp);
	closedir(dir);
	return (sort_dir(dir_list, opt));
}

void	view_dir(char *d, t_opt *opt)
{
	DIR *dir;
	struct dirent *entry;
	struct stat i_entry;
	char path_name[PATH_MAX + 1];
	
	dir = opendir(d);
	while ((entry = readdir(dir)))
	{
		if (ft_strncmp(entry->d_name, ".", PATH_MAX) &&
			ft_strncmp(entry->d_name, "..", PATH_MAX))
		{
			ft_strncpy(path_name, d, PATH_MAX);
			ft_strncat(path_name, "/", PATH_MAX);
			ft_strncat(path_name, entry->d_name, PATH_MAX);
			stat(path_name, &i_entry);
			if (S_ISDIR(i_entry.st_mode))
			{
				printf("\n%s:\n", path_name);
				print_list(path_name, opt);
			}
		}
	}
	closedir(dir);
}

// void	apply_opt(char *d, t_dlist **list, t_opt *opt)
// {
// 	struct dirent *d_dir;
// 	t_dlist *dir_list;
// 	DIR *dir;

// 	if (opt->R == 1)
// 	{
// 		dir = opendir(d);
// 		while ((d_dir = readdir(dir)))
// 			if ()
// 	}
// }

void	print_list(char *d, t_opt *opt)
{
	t_dlist *list;

	if (!(list = read_dir(d, opt)))
		return ;
	// apply_opt(d, &list, opt);
	while (list)
	{
		if (list->name[0] != '.' || (list->name[0] == '.' && opt->a == 1))
			printf("%s\n", list->name);
		list = list->next;
	}
	free(list);
	if (opt->rr == 1)
		view_dir(d, opt);
	// if (opt->rr == 1)
	// {
	// 	dir = opendir(d);
	// 	while ((d_dir = readdir(dir)))
	// 	{
	// 		printf("========%s\n", d_dir->d_name);
	// 		if (d_dir->d_type == 4)
	// 		{
	// 			tmp = ft_strjoin(d, "/");
	// 			s = ft_strjoin(tmp, d_dir->d_name);
	// 			// free (tmp);
	// 			print_list(s, opt);
	// 			// free (s);
	// 		}
	// 	}
	// }
}

void	check_directory(int ac, char **av, t_opt *opt, int i)
{
	if (i == ac)
		print_list(getenv("PWD"), opt);
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