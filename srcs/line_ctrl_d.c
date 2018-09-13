/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_ctrl_d.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saxiao <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/27 15:43:52 by saxiao            #+#    #+#             */
/*   Updated: 2018/09/13 17:01:07 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "line_edit.h"

int			delete_at_position(t_line *line)
{
	if (line->pos < line->buf_len)
	{
		move_right(line);
		delete_key(line);
		move_left(line);
	}
	return (0);
}

int			ctrl_d(t_line *line)
{
	if (g_with_termcap && line->buf_len)
		delete_at_position(line);
	else
	{
		if (g_inside_doc_quote)
		{
			g_dld = 1;
			g_inside_doc_quote = 0;
			return (0);
		}
		else
		{
			init_attr(SETOLD);
			ft_putendl("exit");
			exit(0);
		}
	}
	return (0);
}

int			ctrl_c(char *new_line, t_line *line)
{
	(void)new_line;
	ft_bzero(new_line, INPUT_MAX_LEN);
	g_clc = 1;
	free_auto_lt(line);
	line->auto_ct = -1;
	is_tab(CONTRL_C, line);
	init_attr(SETOLD);
	return (0);
}
