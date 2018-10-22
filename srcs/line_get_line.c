/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_get_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saxiao <saxiao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/27 15:48:30 by saxiao            #+#    #+#             */
/*   Updated: 2018/10/19 16:37:01 by saxiao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <curses.h>
#include <term.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include "line_edit.h"
#include "global.h"

void		init_line(char *prompt, t_line *line)
{
	ft_bzero(line->buf, INPUT_MAX_LEN);
	ft_bzero(line->ici_doc, INPUT_MAX_LEN);
	ft_bzero(line->auto_compare, INPUT_MAX_LEN);
	ft_bzero(line->prompt, INPUT_MAX_LEN);
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
	line->in_heredoc = 0;
	line->end_line = 0;
	line->dld = 0;
	line->clc = 0;
	line->auto_last_choice_len = -1;
	g_with_termcap = 1;
	ft_strcpy(line->prompt, prompt);
}

static void	help_for_line(char *new_line, char *prompt)
{
	ft_bzero(new_line, INPUT_MAX_LEN);
	print_prompt(prompt);
}

static void	get_line_without_termcaps(char *new_line)
{
	char			*ligne;

	ligne = NULL;
	g_with_termcap = 0;
	if (get_next_line(1, &ligne) == 0)
		exit(0);
	ligne ? ft_strcpy(new_line, (const char *)ligne) : (void)ligne;
	ligne ? free(ligne) : (void)ligne;
}
#include "init.h"
int			get_line(char *prompt, char *new_line, t_line *line, t_env **env)
{
	unsigned long	key;

	help_for_line(new_line, prompt);
	init_signals();
	if (init_attr(ADVANCED_LINE_EDIT) == 0)
	{
		init_line(prompt, line);
		while (((key = get_key(line)) && !(!line->is_tabb4 &&  key == '\n')) \
				&& !line->clc && !line->dld)
		{
			if (key == CONTRL_C)
				return (ctrl_c(new_line, line));
			engine(line, key, env);
			if (g_winsize_changed)
				winsize_change(line);
		}
		init_attr(BASIC_LINE_EDIT);
		ft_strcpy(new_line, (const char *)line->buf);
	}
	else
		get_line_without_termcaps(new_line);
	return (0);
}
