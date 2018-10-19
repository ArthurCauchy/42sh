/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_ctrl_d.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saxiao <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/27 15:43:52 by saxiao            #+#    #+#             */
/*   Updated: 2018/10/19 16:31:38 by saxiao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <curses.h>
#include <term.h>
#include <stdlib.h>
#include "../headers/line_edit.h"
#include "../libft/ft_printf/includes/ft_printf.h"
#include "../headers/global.h"

void		print_prompt(char *prompt)
{

	init_attr(BASIC_LINE_EDIT);
	boldgreen();
	ft_printf("%s",prompt);
	color_reset();
	init_attr(ADVANCED_LINE_EDIT);
}

static void	reprint_line(t_line *line)
{
	int				pos_saver;
	char			buf_saver[INPUT_MAX_LEN];
	int				i;

	i = -1;
	pos_saver = line->pos;
	ft_bzero(buf_saver, INPUT_MAX_LEN);
	ft_strcpy(buf_saver, (char *)line->buf);
	ft_bzero(line->buf, INPUT_MAX_LEN);
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
	tputs(tgetstr("cl", 0), 1, my_putc);
	print_prompt(line->prompt);
	reprint_line(line);
	return (0);
}

int			winsize_change(t_line *line)
{
	move_nleft(line);
	init_line(line->prompt, line);
	print_prompt(line->prompt);
	reprint_line(line);
	g_winsize_changed = 0;
	return (0);
}
