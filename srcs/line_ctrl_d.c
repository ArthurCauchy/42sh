/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_ctrl_d.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saxiao <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/27 15:43:52 by saxiao            #+#    #+#             */
/*   Updated: 2018/11/16 18:34:47 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <curses.h>
#include <term.h>
#include <stdlib.h>
#include "line_edit.h"
#include "ft_printf.h"
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

int			ctrl_d(t_line *line)
{
	if (g_with_termcap && line->buf_len)
		delete_at_position(line);
	else
	{
		if (line->is_special_prompt)
		{
			line->dld = 1;
			free_auto_lt(line);
			line->auto_ct = -1;
			is_tab(CONTRL_D, line);
			init_attr(BASIC_LINE_EDIT);
			return (1);
		}
		else
		{
			init_attr(BASIC_LINE_EDIT);
			ft_putendl("exit");
			history_exit();
			clear_builtins();
			clear_env(g_env);
			exit(0);
		}
	}
	return (0);
}

int			ctrl_c(char *new_line, t_line *line)
{
	ft_bzero(new_line, INPUT_MAX_LEN);
	line->clc = 1;
	free_auto_lt(line);
	line->auto_ct = -1;
	is_tab(CONTRL_C, line);
	init_attr(BASIC_LINE_EDIT);
	return (1);
}
