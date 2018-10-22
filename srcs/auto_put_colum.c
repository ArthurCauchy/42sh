/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_put_colum.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saxiao <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/17 17:33:25 by saxiao            #+#    #+#             */
/*   Updated: 2018/10/22 11:37:47 by saxiao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "line_edit.h"

static int			jump_list(t_line *line, int *total_row)
{
	int		row;
	int		nb_row_command;
	int		i;
	t_autolist	*cp;

	*total_row = line->w.line;
	i = line->auto_ct % nb_list(line->auto_lt) + 1;
	cp = line->auto_lt;
	while (--i > 0)
		cp = cp->next;
	nb_row_command = (line->buf_len + ft_strlen(cp->name) - \
			ft_strlen((char *)line->auto_compare)- 1) / line->line_max + 1;
	if (line->screen_height - nb_row_command - line->w.line - 1 < 0)
		*total_row = line->screen_height - nb_row_command - 1;
	if (line->auto_ct < 0)
		return (0);
	row = line->auto_ct % nb_list(line->auto_lt) % line->w.line + 1;
	if (nb_row_command + row  + 1 <= line->screen_height)
		return (0);
	return (row  + 3 - line->screen_height - nb_row_command);
}

static t_autolist	*start_list(t_line *line, int *total_row)
{
	int		i;
	t_autolist	*cp;

	i = jump_list(line, total_row) + 1;
	cp = line->auto_lt;
	while (--i > 0)
		cp = cp->next;
	return (cp);
}

static void			for_put_colum(t_line *line, t_autolist *cp)
{
	if (cp->is_dic)
		blue();
	if (cp->ct == line->auto_ct % nb_list(line->auto_lt))
	{
		line->auto_is_dic = cp->is_dic;
		bg_yellow();
	}
	ft_printf("%-*s", line->w.max, cp->name);
	color_reset();
}

void				put_colum(t_line *line)
{
	t_autolist	*cp;
	t_autolist	*lt;
	t_helper	ct;
	int			total_row;;

	ct.j = -1;
	total_row = line->w.line;
	lt = start_list(line, &total_row);
	while (++(ct.j) < total_row)
	{
		cp = lt;
		ct.i = -1;
		while (++(ct.i) < line->w.col && cp)
		{
			ct.index = 0;
			if (cp)
				for_put_colum(line, cp);
			while (cp && (ct.index)++ < line->w.line)
				cp = cp->next;
		}
		ft_printf("\n");
		lt = lt->next;
	}
}
