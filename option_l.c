/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashulha <ashulha@student.us.org>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/06 19:34:59 by ashulha           #+#    #+#             */
/*   Updated: 2017/05/06 19:35:03 by ashulha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	link_l(int st_nlink, int len)
{
	int diff;
	char *tmp;

	tmp = ft_itoa_base(st_nlink, 10);
	diff = len - ft_strlen(tmp);
	while (diff-- > 0)
		printf(" ");
	printf("%d ", st_nlink);
	free(tmp);
}

void	user_id(uid_t user, int len)
{
	int diff;

	diff = len - ft_strlen(getpwuid(user)->pw_name);
	while (diff-- > 0)
		printf(" ");
	printf("%s  ", getpwuid(user)->pw_name);
}

void	size_l(intmax_t size, int len)
{
	int diff;
	char *tmp;

	tmp = ft_itoa_base(size, 10);
	diff = len - ft_strlen(tmp);
	while (diff-- > 0)
		printf(" ");
	printf("%s ", tmp);
	free(tmp);
}

void	gr_id(gid_t group, int len_gr, intmax_t size, int len_s)
{
	int diff;

	diff = len_gr - ft_strlen(getgrgid(group)->gr_name);
	printf("%s  ", getgrgid(group)->gr_name);
	while (diff-- > 0)
		printf(" ");
	size_l(size, len_s);
}
