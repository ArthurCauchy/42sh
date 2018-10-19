/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_ctrl_d.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saxiao <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/27 15:43:52 by saxiao            #+#    #+#             */
/*   Updated: 2018/10/19 14:23:33 by saxiao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <curses.h>
#include <term.h>
#include <stdlib.h>
#include "line_edit.h"
#include "global.h"

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

int			my_clear_screen(t_line *line)
{
	(void)line;
	tputs(tgetstr("cl", 0), 1, my_putc);
	return (0);
}

int			ctrl_d(t_line *line)
{
	if (g_with_termcap && line->buf_len)
		delete_at_position(line);
	else
	{
		if (line->in_heredoc)
		{
			line->dld = 1;
			line->in_heredoc = 0;
			return (0);
		}
		else
		{
			init_attr(BASIC_LINE_EDIT);
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
	line->clc = 1;
	free_auto_lt(line);
	line->auto_ct = -1;
	is_tab(CONTRL_C, line);
	init_attr(BASIC_LINE_EDIT);
	return (0);
}
