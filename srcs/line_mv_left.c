/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_mv_left_right.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saxiao <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/27 15:50:31 by saxiao            #+#    #+#             */
/*   Updated: 2018/11/08 23:30:10 by saxiao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <curses.h>
#include <term.h>
#include "line_edit.h"

int			newline_b4(t_line *line, int index)
{
	int		i;
	int		j;

	i = index - 1;
	j = 0;
	while (i >= 0)
	{
		if (line->buf[i] == '\n')
			return (++j);
		j++;
		i--;
	}
	return (0);
}

static int	case_newline(t_line *line)
{
	int		i;
	int		j;

	i = line->pos - 1;
	if (line->buf[i] != '\n')
		return (line->line_max);
	j = 0;
	while (--i >= 0 && line->buf[i] != '\n')
		j++;
	if (!newline_b4(line, line->pos - 1))
		j += line->start_po;
	if (j > line->line_max)
		j = j % line->line_max;
	return (j);
}

int			move_left(t_line *line)
{
	int		i;
	int		nb;

	i = 0;
	if (line->pos)
	{
		if ((line->pos + line->start_po > line->line_max - 1 && \
					((line->pos + line->start_po) % line->line_max == 0)) \
				|| line->buf[line->pos - 1] == '\n')
		{
			tputs(tgetstr("up", 0), 1, my_putc);
			nb = case_newline(line);
			while (i++ < nb)
				tputs(tgetstr("nd", 0), 1, my_putc);
		}
		else
			tputs(tgetstr("le", 0), 1, my_putc);
		line->pos -= 1;
	}
	return (0);
}

int			move_nleft(t_line *line)
{
	while (line->pos > 0)
		move_left(line);
	return (0);
}

int			mv_left_word(t_line *line)
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
			move_left(line);
	}
	return (0);
}
