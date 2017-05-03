#include <sys/types.h>
#include <sys/xattr.h>
#include <sys/types.h>
#include <sys/acl.h>
#include <stdio.h>

void	opt_set(s_opt *opt)
{
	opt->l = 0;
	opt->rr = 0;
	opt->a = 0;
	opt->r = 0;
	opt->t = 0;
}

int		option(char *s, s_opt *opt)
{
	opt_set(opt);

	if (!(++s))
		return (1);
	while (s)
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
			printf("./ft_ls: illigal option -- %c\n", *s);
			printf("usage: ./ft_ls [-Ralrt] [file ...]\n");
			return (0);
		}
		s++;
	}
	return (1);
}

// void	current_dir(s_opt *opt)
// {
// 	int		id;
// 	DIR		*dir;
// 	char	*d;

// 	id = getuid();
// 	d = getpwuid(id)->pw_dir;
// 	dir = opendir(d);
// 	apply_opt()	
// }

// void	directory(int ac, char **av, s_opt *opt, int i)
// {
// 	if (i == ac - 1)
// 		current_dir(opt);
// }

int		main(int ac, char **av)
{
	int i;
	struct s_opt opt;

	i = 1;
	if (*av[1] == '-')
	{
		if (!option(av[1]), &opt)
			return (0);
		i++;
	}
	// directory(ac, av, &opt, i);
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