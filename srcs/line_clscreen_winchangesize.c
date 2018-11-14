/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_clscreen_winchangesize.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 18:51:28 by acauchy           #+#    #+#             */
/*   Updated: 2018/11/14 13:00:05 by saxiao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <curses.h>
#include <term.h>
#include <stdlib.h>
#include "line_edit.h"
#include "ft_printf.h"
#include "global.h"

void		print_prompt(char *prompt)
{
	init_attr(BASIC_LINE_EDIT);
	boldgreen();
	ft_printf("%s", prompt);
	color_reset();
	init_attr(ADVANCED_LINE_EDIT);
}

static void	reprint_line(t_line *line)
{
	int				pos_saver;
	char			buf_saver[INPUT_MAX_LEN];
	char			prompt_saver[INPUT_MAX_LEN];
	int				i;

	i = -1;
	pos_saver = line->pos;
	ft_bzero(buf_saver, INPUT_MAX_LEN);
	ft_bzero(prompt_saver, INPUT_MAX_LEN);
	ft_strcpy(buf_saver, (char *)line->buf);
	ft_strcpy(prompt_saver, (char *)line->prompt);
	ft_bzero(line->buf, INPUT_MAX_LEN);
	init_line(prompt_saver, line);
	print_prompt(line->prompt);
	line->pos = 0;
	line->buf_len = 0;
	while (++i < (int)ft_strlen(buf_saver))
		printable(line, buf_saver[i]);
	i = line->buf_len - pos_saver + 1;
	while (--i)
		move_left(line);
}

int			my_clear_screen(t_line *line)
{
	if (line->auto_lt)
		free_auto_lt(line);
	tputs(tgetstr("cl", 0), 1, my_putc);
	reprint_line(line);
	return (0);
}

int			winsize_change(t_line *line)
{
	int		nb_line;

	nb_line = (line->buf_len + line->start_po) / line->line_max;
	if ((line->buf_len + line->start_po) % line->line_max)
		nb_line++;
	init_attr(BASIC_LINE_EDIT);
	ft_printf("\n");
	init_attr(ADVANCED_LINE_EDIT);
	while (--nb_line >= 0)
		tputs(tgetstr("up", 0), 1, my_putc);
	tputs(tgetstr("cd", 0), 1, my_putc);
	if (line->auto_lt)
		free_auto_lt(line);
	reprint_line(line);
	g_winsize_changed = 0;
	return (0);
}
