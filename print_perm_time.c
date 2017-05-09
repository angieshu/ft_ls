/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_perm.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashulha <ashulha@student.us.org>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/09 14:45:56 by ashulha           #+#    #+#             */
/*   Updated: 2017/05/09 14:45:57 by ashulha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

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

void	mode(mode_t st_mode, char *file, int st_nlink, int len)
{
	char *perm;

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
