/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_func.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashulha <ashulha@student.us.org>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/09 14:48:42 by ashulha           #+#    #+#             */
/*   Updated: 2017/05/09 14:48:43 by ashulha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	opt_reset(t_opt *opt)
{
	opt->l = 0;
	opt->a = 0;
	opt->r = 0;
	opt->t = 0;
	opt->f = 0;
	opt->u = 0;
	opt->g = 0;
	opt->d = 0;
	opt->rr = 0;
	opt->tt = 0;
	opt->none = 0;
}

void	opt_set(t_len *l)
{
	l->lnk = 1;
	l->us = 1;
	l->gr = 1;
	l->size = 1;
	l->total = 0;
}

void	list_set(t_output **out)
{
	*out = (t_output*)ft_memalloc(sizeof(t_output));
	(*out)->notexist = NULL;
	(*out)->notdir = NULL;
	(*out)->dir = NULL;
}

char	*path(char *path_name, char *curr_dir, char *file_name)
{
	ft_strncpy(path_name, curr_dir, PATH_MAX);
	ft_strncat(path_name, "/", PATH_MAX);
	ft_strncat(path_name, file_name, PATH_MAX);
	return (path_name);
}
