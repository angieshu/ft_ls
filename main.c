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
	if (!ft_strcmp("--", s))
		return (1);
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
		else
		{
			printf("./ft_ls: illegal option -- %c\n", *s);
			printf("usage: ./ft_ls [-Ralrt] [file ...]\n");
			return (0);
		}
		++s;
	}
	return (1);
}

t_list	*read_dir(char *d, t_opt *opt)
{
	struct dirent	*d_dir;
	t_list			*dir_list;
	DIR				*dir;

	dir_list = NULL;
	if (!(dir = opendir(d)))
		return (NULL);
	while ((d_dir = readdir(dir)))
	{
		if (!(d_dir->d_name[0] == '.' && opt->a != 1))
			if (!list_add(&dir_list, d_dir->d_name, d_dir->d_namlen))
				return (NULL);
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
			path(path_name, d, entry->d_name);
			stat(path_name, &i_entry);
			if (S_ISDIR(i_entry.st_mode))
				if (!list_add(&list, path_name, ft_strlen(path_name)))
					return (NULL);
		}
	}
	closedir(dir);
	return (sort_dir(list, opt));
}

void	path(char *path_name, char *curr_dir, char *file_name)
{
	ft_strncpy(path_name, curr_dir, PATH_MAX);
	ft_strncat(path_name, "/", PATH_MAX);
	ft_strncat(path_name, file_name, PATH_MAX);
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
	// apply_opt(d, &list, opt);
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