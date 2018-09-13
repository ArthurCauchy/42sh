/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_paste_go_updown.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saxiao <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/27 15:51:22 by saxiao            #+#    #+#             */
/*   Updated: 2018/09/13 14:40:06 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <curses.h>
#include <term.h>
#include "line_edit.h"

int		cut_end(t_line *line)
{
	int		i;

	i = line->buf_len - line->pos;
	cp_end(line);
	move_nright(line);
	while (i--)
		delete_key(line);
	return (0);
}

int		paste(t_line *line)
{
	int		index;
	int		i;
	char	rest[MAX_BUF];

	index = line->pos;
	ft_bzero(rest, MAX_BUF);
	ft_strcpy(rest, (char *)line->buf + index);
	i = 0;
	if (line->buf_len + ft_strlen(rest) < MAX_BUF - 1)
	{
		while (line->cp[i])
			line->buf[index++] = line->cp[i++];
		i = 0;
		while (rest[i])
			line->buf[index++] = rest[i++];
		i = line->buf_len - line->pos;
		line->buf_len = line->pos;
		index = line->pos;
		while (line->buf[index])
			put_a_key(line, line->buf[index++]);
		while (i--)
			move_left(line);
	}
	return (0);
}

int		go_up(t_line *line)
{
	int		i;

	if (line->pos > line->line_max - line->start_po - 1)
	{
		tputs(tgetstr("up", 0), 1, my_putc);
		line->pos = line->pos - line->line_max;
		if ((line->pos + line->start_po) / line->line_max == 0 && \
				(line->pos + line->start_po) % line->line_max < line->start_po)
		{
			i = line->start_po - (line->pos + line->start_po) % line->line_max;
			while (i--)
				move_right(line);
		}
	}
	return (0);
}

int		go_down(t_line *line)
{
	int		i;

	if ((line->buf_len - 1 + line->start_po) / line->line_max >
			(line->pos + line->start_po) / line->line_max)
	{
		tputs(tgetstr("do", 0), 1, my_putc);
		line->pos = line->pos + line->line_max;
		if (line->pos > line->buf_len - 1)
		{
			i = line->pos - (line->buf_len - 1);
			while (i--)
				move_left(line);
		}
	}
	return (0);
}
