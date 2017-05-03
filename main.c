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

void	apply_opt(char *d, t_opt *opt)
{
	DIR		*dir;
	struct dirent *d_dir;

	dir = opendir(d);
	while ((d_dir = readdir(dir)))
		printf("%s\n", d_dir->d_name);
	closedir(dir);
}

void	current_dir(t_opt *opt)
{
	// int		id;
	// DIR		*dir;
	char	*d;
	// id = getuid();
	// d = getpwuid(id)->pw_dir;
	d = getenv("PWD");
	apply_opt(d, opt);	
}

void	check_directory(int ac, char **av, t_opt *opt, int i)
{
	if (i == ac)
		current_dir(opt);
}

int		main(int ac, char **av)
{
	int i;
	t_opt opt;

	i = 1;
	opt_reset(&opt);
	if (*av[1] == '-')
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