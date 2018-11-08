/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_put_colum.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saxiao <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/17 17:33:25 by saxiao            #+#    #+#             */
/*   Updated: 2018/11/08 23:44:38 by saxiao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "line_edit.h"

static int			jump_list(t_line *line, int *total_row)
{
	int			row;
	int			nb_row_command;

	*total_row = line->w.line;
	nb_row_command = nb_line_command(line);
	if (line->screen_height - nb_row_command - line->w.line < 0)
		*total_row = line->screen_height - nb_row_command;
	line->real_nb_auto_line = *total_row;
	if (line->auto_ct < 0)
		return (0);
	row = line->auto_ct % nb_list(line->auto_lt) % line->w.line + 1;
	if (nb_row_command + row <= line->screen_height)
		return (0);
	return (row - (line->screen_height - nb_row_command));
}

static t_autolist	*start_list(t_line *line, int *total_row)
{
	int			i;
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
	int			total_row;

	ct.j = 0;
	total_row = line->w.line;
	lt = start_list(line, &total_row);
	while (++(ct.j) <= total_row)
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
		if (ct.j < total_row)
			ft_printf("\n");
		lt = lt->next;
	}
}
