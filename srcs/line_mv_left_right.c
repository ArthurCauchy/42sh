/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_mv_left_right.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saxiao <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/27 15:50:31 by saxiao            #+#    #+#             */
/*   Updated: 2018/09/13 14:38:28 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <curses.h>
#include <term.h>
#include "line_edit.h"

int		move_left(t_line *line)
{
	int i;

	i = 0;
	if (line->pos)
	{
		if ((line->pos + line->start_po) % line->line_max == 0)
		{
			tputs(tgetstr("up", 0), 1, my_putc);
			while (i++ < line->line_max)
				tputs(tgetstr("nd", 0), 1, my_putc);
		}
		else
			tputs(tgetstr("le", 0), 1, my_putc);
		line->pos -= 1;
	}
	return (0);
}

int		move_nleft(t_line *line)
{
	while (line->pos > 0)
		line->move_left(line);
	return (0);
}

int		mv_left_word(t_line *line)
{
	int		left;

	left = line->pos;
	if (line->pos == line->buf_len)
		left = line->buf_len - 1;
	if (line->pos != line->buf_len && left && line->buf[left] != ' ' && \
			line->buf[left] != '\t' && (line->buf[left - 1] == ' ' \
			|| line->buf[left - 1] == '\t'))
		left--;
	while (left > 0 && (line->buf[left] == ' ' || line->buf[left] == '\t'))
		left--;
	if (line->buf[left] != ' ' && line->buf[left] != '\t')
	{
		while (left > 0 && line->buf[left] != ' ' && line->buf[left] != '\t')
			left--;
		if (left)
			left++;
		while (line->pos > left)
			line->move_left(line);
	}
	return (0);
}

int		mv_right_word(t_line *l)
{
	int		rt;

	rt = l->pos;
	if (rt != l->buf_len)
	{
		while (rt < l->buf_len && l->buf[rt] != ' ' && l->buf[rt] != '\t')
			rt++;
		while (rt < l->buf_len && (l->buf[rt] == ' ' || l->buf[rt] == '\t'))
			rt++;
		if (rt < l->buf_len && rt - 1 >= 0 && (l->buf[rt - 1] == ' ' \
		|| l->buf[rt - 1] == '\t') && l->buf[rt] != ' ' && l->buf[rt] != '\t')
		{
			while (l->pos < rt)
				l->move_right(l);
		}
	}
	return (0);
}

int		move_right(t_line *line)
{
	int		i;

	i = line->line_max;
	if (line->pos < line->buf_len)
	{
		if ((line->pos + line->start_po) % line->line_max == line->line_max - 1)
		{
			tputs(tgetstr("do", 0), 1, my_putc);
			while (i-- > 0)
				tputs(tgetstr("le", 0), 1, my_putc);
		}
		else
			tputs(tgetstr("nd", 0), 1, my_putc);
		line->pos += 1;
	}
	return (0);
}
