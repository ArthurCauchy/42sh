/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_delete.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saxiao <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/27 17:43:38 by saxiao            #+#    #+#             */
/*   Updated: 2018/11/08 23:24:18 by saxiao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <curses.h>
#include <term.h>
#include "line_edit.h"

int			move_nright(t_line *line)
{
	while (line->pos < line->buf_len)
		move_right(line);
	return (0);
}

static int	remove_all(t_line *line)
{
	move_nleft(line);
	tputs(tgetstr("cr", 0), 1, my_putc);
	tputs(tgetstr("cd", 0), 1, my_putc);
	print_prompt(line->prompt);
	return (0);
}

int			delete_key(t_line *l)
{
	int		i;
	int		new_pos;
	char	cp[INPUT_MAX_LEN];

	if (l->pos > 0)
	{
		i = l->pos - 2;
		new_pos = l->pos - 1;
		remove_all(l);
		while (++i < l->buf_len)
			l->buf[i] = l->buf[i + 1];
		ft_bzero(cp, INPUT_MAX_LEN);
		ft_strcpy(cp, (char *)l->buf);
		ft_bzero(l->buf, INPUT_MAX_LEN);
		i = 0;
		l->buf_len = 0;
		l->pos = 0;
		init_attr(ADVANCED_LINE_EDIT);
		while (cp[i])
			printable(l, cp[i++]);
		i = l->buf_len - new_pos;
		while (i-- > 0)
			move_left(l);
	}
	return (0);
}

int			delete_all(t_line *line)
{
	remove_all(line);
	line->buf_len = 0;
	line->pos = 0;
	ft_bzero(line->buf, INPUT_MAX_LEN);
	return (0);
}
