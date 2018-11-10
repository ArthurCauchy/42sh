/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_printable.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saxiao <saxiao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/27 15:52:08 by saxiao            #+#    #+#             */
/*   Updated: 2018/11/10 12:03:56 by ccharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <curses.h>
#include <term.h>
#include <unistd.h>
#include "line_edit.h"

void		put_a_key(t_line *line, unsigned long key)
{
	if (!not_last_letter(line))
	{
		tputs(tgetstr("ic", 0), 1, my_putc);
		for_put_a_key(line, key);
		tputs(tgetstr("do", 0), 1, my_putc);
		tputs(tgetstr("cr", 0), 1, my_putc);
	}
	else
		for_put_a_key(line, key);
	line->pos++;
	line->buf_len++;
}

static void	for_printable(t_line *line, unsigned long key, int *index)
{
	*index = line->buf_len;
	while (*index > line->pos)
	{
		line->buf[*index] = line->buf[*index - 1];
		*index = *index - 1;
	}
	line->buf[line->pos] = key;
	*index = line->pos;
	line->buf_len = line->pos;
}

static int	for_printable_2(t_line *line, unsigned long key)
{
	line->buf[line->pos] = key;
	put_a_key(line, key);
	return (0);
}

static void	update_index(t_line *line, int hint, int new_pos, int *index)
{
	if (hint)
		*index = (line->buf_len + line->start_po) / line->line_max - \
			(new_pos + line->start_po) / line->line_max;
	else
		*index = (line->buf_len + line->start_po) % line->line_max - \
			(new_pos + line->start_po) % line->line_max;
}

int			printable(t_line *line, unsigned long key)
{
	int		index;
	int		new_pos;
	int		new_len;
	int		i;

	if (line->buf_len + line->start_po >= INPUT_MAX_LEN - 1)
		return (0);
	if (line->pos == line->buf_len)
		return (for_printable_2(line, key));
	new_pos = line->pos + 1;
	new_len = line->buf_len + 1;
	for_printable(line, key, &index);
	while (index < new_len)
		put_a_key(line, line->buf[index++]);
	update_index(line, 1, new_pos, &index);
	i = line->buf_len - new_pos + 1;
	while (--i)
		move_left(line);
	return (0);
}
