#ifndef FT_LS_H
# define FT_LS_H
# include "libft/libft.h"
// # include "libftprintf.h"
# include <dirent.h>
# include <unistd.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <pwd.h>
# include <uuid/uuid.h>
# include <sys/xattr.h>
# include <grp.h>
# include <stdio.h>
# include <stdlib.h>
# include <errno.h>

typedef struct	s_opt
{
	int l;
	int rr;
	int a;
	int r;
	int t;
	int none;
}				t_opt;

typedef	struct	s_dlist
{
	char			*name;
	struct s_dlist	*next;
}				t_dlist;

t_dlist		*sort_dir(t_dlist *head, t_opt *opt);
t_dlist		*merge_list(t_dlist *a, t_dlist *b, t_opt *opt);
void		print_list(char *d, t_opt *opt);

#endif