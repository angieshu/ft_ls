#ifndef FT_LS_H
# define FT_LS_H
# include "libft/libft.h"
// # include "libftprintf.h"
# include <dirent.h>
# include <unistd.h>
# include <sys/stat.h>
# include <sys/dir.h>
# include <sys/types.h>
# include <sys/acl.h>
# include <pwd.h>
# include <uuid/uuid.h>
# include <sys/xattr.h>
# include <grp.h>
# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <time.h>

typedef struct		s_opt
{
	int l;
	int a;
	int r;
	int t;
	int f;
	int u;
	int rr;
	int tt;
	int none;
}					t_opt;

t_list		*sort_dir(t_list *head, t_opt *opt);
t_list		*sort_list(t_list *head, t_opt *opt);
t_list		*merge_list(t_list *a, t_list *b, t_opt *opt, intmax_t k);
t_list		*listrev(t_list *list);

int			list_add(t_list **head, char *name, size_t size);
void		print_list(char *d, t_opt *opt);
char		*path(char *path_name, char *curr_dir, char *file_name);


#endif