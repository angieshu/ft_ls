#ifndef FT_LS_H
# define FT_LS_H
# include "../includes/libft/libft.h"
# include "../includes/ft_printf/src/libftprintf.h"
# include <dirent.h>
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

typedef struct	s_opt
{
	int l;
	int a;
	int r;
	int t;
	int f;
	int u;
	int g;
	int d;
	int rr;
	int tt;
	int none;
}				t_opt;

typedef struct	s_len
{
	int lnk;
	int us;
	int gr;
	int size;
	int total;
}				t_len;

typedef struct	s_output
{
	t_list *notexist;
	t_list *notdir;
	t_list *dir;
}				t_output;

t_list		*sort_dir(t_list *head, t_opt *opt);
t_list		*sort_list(t_list *head, t_opt *opt, int flag);
t_list		*merge_list(t_list *a, t_list *b, t_opt *opt, intmax_t k,int flag);
t_list		*listrev(t_list *list);

int			list_add(t_list **head, char *name, size_t size);
void		list_add_back(t_list *head, char *name, size_t size);

char		*path(char *path_name, char *curr_dir, char *file_name);

void		opt_set(t_len *l);
void		min_width(t_list *list, t_list *original, t_opt *opt, t_len *l);
void		apply_opt(t_list *list, t_list *original, t_opt *opt, t_len l);
void		link_l(int st_nlink, int len);
void		user_id(uid_t user, int len);
void		size_l(intmax_t size, int len);
void		gr_id(gid_t group, int len_gr, intmax_t size, int len_s);
void		permitions(char *perm, int len);
void		attrib(char *file);
void		mode(mode_t st_mode, char *file, int st_nlink, int len);
void		time_s(time_t tim, t_opt *opt, char *content);
void		apply_l(t_list *dir_list, char *dir, t_opt *opt);


void		opt_reset(t_opt *opt);
void		opt_set(t_len *l);
void		list_set(t_output **out);
char		*path(char *path_name, char *curr_dir, char *file_name);

void		print_list(char *d, t_opt *opt);
void		print_dir(char *curr_dir, t_opt *opt);
void		print_output(t_list *list, t_opt *opt);
void		print_output_dir(t_list *list, t_opt *opt, int flag);
void		check_dir(char **av, int i, int ac, t_opt *opt, int flag);
void		print_list(char *d, t_opt *opt);
t_list		*view_dir(char *d, t_opt *opt);
t_list		*read_dir(char *d, t_opt *opt);
int			option(char **s, t_opt *opt);

void		free_list(t_list **list);
void		free_out(t_output *out);
#endif