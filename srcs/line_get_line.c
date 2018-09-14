/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_get_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saxiao <saxiao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/27 15:48:30 by saxiao            #+#    #+#             */
/*   Updated: 2018/09/14 12:40:44 by lumenthi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <curses.h>
#include <term.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include "line_edit.h"

static void				for_init_line(t_line *line)
{
	line->printable = printable;
	line->move_left = move_left;
	line->move_right = move_right;
	line->move_nleft = move_nleft;
	line->move_nright = move_nright;
	line->delete_key = delete_key;
	line->mv_left_word = mv_left_word;
	line->mv_right_word = mv_right_word;
	line->history_up = history_up;
	line->history_down = history_down;
	line->cp_all = cp_all;
	line->cp_begin = cp_begin;
	line->cp_end = cp_end;
	line->cut_all = cut_all;
	line->cut_begin = cut_begin;
	line->cut_end = cut_end;
	line->paste = paste;
	line->go_up = go_up;
	line->go_down = go_down;
	line->ctrl_d = ctrl_d;
	line->return_key = return_key;
	line->delete_at_position = delete_at_position;
	line->engine = engine;
}

void					init_line(char *prompt, t_line *line)
{
	ft_bzero(line->buf, INPUT_MAX_LEN);
	ft_bzero(line->ici_doc, INPUT_MAX_LEN);
	ft_bzero(line->auto_compare, INPUT_MAX_LEN);
	line->pos = 0;
	line->buf_len = 0;
	line->line_max = tgetnum("co");
	line->screen_height = tgetnum("li");
	line->start_po = ft_strlen(prompt);
	line->his_mostdown = 1;
	line->his_mostup = 0;
	line->up_indown = 0;
	line->one_his = 0;
	line->is_tabb4 = 0;
	line->auto_ct = -1;
	line->auto_lt = NULL;
	line->auto_is_dic = 0;
	g_with_termcap = 1;
	for_init_line(line);
}

static void				help_for_line(char **ligne, char *new_line, char *pt)
{
	ft_bzero(new_line, INPUT_MAX_LEN);
	*ligne = NULL;
	g_end_line = 0;
	init_attr(SETOLD);
	ft_putstr(pt);
	g_clc = 0;
	g_dld = 0;
}

int						get_line(char *prompt, char *new_line, t_line *line, char **env)
{
	unsigned long	key;
	char			*ligne;

	help_for_line(&ligne, new_line, prompt);
	if (init_attr(SETNEW) == 0)
	{
		init_line(prompt, line);
		while (((key = get_key()) && !(!line->is_tabb4 &&  key == '\n')) && !g_clc && !g_dld)
		{
			if (key == CONTRL_C)
				return (ctrl_c(new_line, line));
			line->engine(line, key, env);
		}
		init_attr(SETOLD);
		ft_strcpy(new_line, (const char *)line->buf);
	}
	else
	{
		g_with_termcap = 0;
		if (get_next_line(1, &ligne) == 0)
			exit(0);
		ligne ? ft_strcpy(new_line, (const char *)ligne) : (void)ligne;
		ligne ? free(ligne) : (void)ligne;
	}
	return (0);
}
