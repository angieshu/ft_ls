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

typedef struct	s_opt
{
	int l;
	int rr;
	int a;
	int r;
	int t;
	int none;
}				t_opt;
#endif