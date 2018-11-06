/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_printable.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saxiao <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/27 15:52:08 by saxiao            #+#    #+#             */
/*   Updated: 2018/11/06 21:51:30 by saxiao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <curses.h>
#include <term.h>
#include <unistd.h>
#include "line_edit.h"

int			not_last_letter(t_line *line)
{
	int		i;

	if ((i = newline_b4(line, line->pos + 1)))
		return (i % line->line_max);
	return ((line->pos + 1 + line->start_po) % line->line_max);
}

void		for_put_a_key(t_line *line, unsigned long key)
{
	(void)line;
	(void)key;
		write(STDOUT_FILENO, &key, 1);
	if (key == '\n')
		tputs(tgetstr("cr", 0), 1, my_putc);
		/*
	else
	{
		init_attr(BASIC_LINE_EDIT);
		write(STDOUT_FILENO, &key, 1);
		init_attr(ADVANCED_LINE_EDIT);
	}
	*/
}

void		put_a_key(t_line *line, unsigned long key)
{
	//if ((line->pos + 1 + line->start_po) % line->line_max == 0)
	if (!not_last_letter(line))
	{
		tputs(tgetstr("ic", 0), 1, my_putc);
		for_put_a_key(line, key);
		tputs(tgetstr("do", 0), 1, my_putc);
		tputs(tgetstr("cr", 0), 1, my_putc);
	//	for_put_a_key(line, key);
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
	int		positive;
	int		new_pos;
	int		new_len;

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
	/*
	while (index-- > 0)
		tputs(tgetstr("up", 0), 1, my_putc);
	update_index(line, 0, new_pos, &index);
	positive = index >= 0 ? index : -index;
	while (positive-- > 0)
		tputs(tgetstr(index > 0 ? "le" : "nd", 0), 1, my_putc);
		*/
	int		i = line->buf_len - new_pos + 1;
	(void)positive;
	while (--i)
		move_left(line);
	return (0);
}
