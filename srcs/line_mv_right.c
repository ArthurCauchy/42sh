/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_mv_left_right.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saxiao <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/27 15:50:31 by saxiao            #+#    #+#             */
/*   Updated: 2018/11/08 23:27:28 by saxiao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <curses.h>
#include <term.h>
#include "line_edit.h"

int			mv_right_word(t_line *l)
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
					|| l->buf[rt - 1] == '\t') && l->buf[rt] != ' ' \
				&& l->buf[rt] != '\t')
		{
			while (l->pos < rt)
				move_right(l);
		}
	}
	return (0);
}

static int	newline_b4_mv_right(t_line *line)
{
	int		i;

	i = line->pos - 1;
	while (i >= 0)
	{
		if (line->buf[i] == '\n')
			return (1);
		i--;
	}
	return (0);
}

static int	right_newline(t_line *line)
{
	int		i;
	int		j;

	i = line->pos;
	if (line->buf[i] != '\n')
		return (line->line_max);
	j = 0;
	while (--i >= 0 && line->buf[i] != '\n')
		j++;
	if (!newline_b4_mv_right(line))
		j += line->start_po;
	return (j);
}

int			move_right(t_line *line)
{
	int		i;

	if (line->pos < line->buf_len)
	{
		if (((line->pos + line->start_po) % line->line_max == \
					line->line_max - 1) || line->buf[line->pos] == '\n')
		{
			tputs(tgetstr("do", 0), 1, my_putc);
			i = right_newline(line);
			while (i-- > 0)
				tputs(tgetstr("le", 0), 1, my_putc);
		}
		else
			tputs(tgetstr("nd", 0), 1, my_putc);
		line->pos += 1;
	}
	return (0);
}
