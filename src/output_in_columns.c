/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_in_columns.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashulha <ashulha@student.us.org>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/11 11:20:53 by ashulha           #+#    #+#             */
/*   Updated: 2017/05/11 11:20:55 by ashulha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	space(char *content, int len)
{
	int diff;

	diff = len - ft_strlen(content);
	while (diff-- > 0)
		ft_printf(" ");
}

void	max_n_col(t_list *list, t_col *w_info)
{
	w_info->col_max = 0;
	w_info->f_len = 0;
	w_info->n_files = 0;

	while (list)
	{
		w_info->f_len = (ft_strlen(list->content) > w_info->f_len) ?
		ft_strlen(list->content) : w_info->f_len;
		w_info->n_files++;
		list = list->next;
	}
	w_info->f_len++;
	w_info->col_max = w_info->w_len / w_info->f_len;
}

void	no_columns(t_list *list, t_col *w_info)
{
	while (list)
	{
		ft_printf("%s", list->content);
		(list->next) ? space(list->content, w_info->f_len) : 0;
		list = list->next;
	}
	ft_printf("\n");
}

void	col_row(t_col *w_info, t_list *list)
{
	(w_info->n_files <= w_info->col_max) ? no_columns(list, w_info) : 0;
	// w_info->col = w_info->col_max / 2;
	w_info->row = 1;
	// while (w_info->col <= w_info->col_max)
	// {
	// 	if (!(w_info->n_files % w_info->col))
	// 	{
	// 		w_info->row = w_info->n_files / w_info->col;
	// 		break ;
	// 	}
	// 	w_info->col++;
	// }
	// if (w_info->col > w_info->col_max && !w_info->row)
	// {
		w_info->col = w_info->col_max;
		ft_printf("====%d\n", w_info->col);
		while (w_info->col >= (w_info->col_max / 2) + 1)
		{
			w_info->row = w_info->n_files / w_info->col;
			if (w_info->row >= (w_info->n_files % w_info->col))
				break ;
			w_info->col--;
		}
		// w_info->col++;
}


void	columns(t_list *list)
{
	t_col w_info;
	int i;
	int n;
	struct winsize w;

	if (!list)
		return ;
	i = 0;
    ioctl(0, TIOCGWINSZ, &w);
    w_info.w_len = w.ws_col;
    max_n_col(list, &w_info);
    col_row(&w_info, list);
    while (get_elem_n(list, i) && i <= w_info.row && w_info.n_files > w_info.col_max)
    {
    	n = i;
    	ft_printf("%s", get_elem_n(list, i));
    	space(get_elem_n(list, i), w_info.f_len);
    	while (get_elem_n(list, n += w_info.row + 1))
    	{
    		ft_printf("%s", get_elem_n(list, n));
    		space(get_elem_n(list, n), w_info.f_len);
    	}
    	ft_printf("\n");
    	i++;
	}
}
