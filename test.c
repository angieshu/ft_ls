/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashulha <ashulha@student.us.org>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 15:11:42 by ashulha           #+#    #+#             */
/*   Updated: 2017/05/03 15:12:04 by ashulha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "ft_ls.h"

int main(int ac, char **av)
{
	struct dirent *Dir;
	DIR *dir;

	dir = opendir(av[1]);
	while ((Dir = readdir(dir)) != NULL)
		printf("%s\n", Dir->d_name);
	closedir(dir);
}