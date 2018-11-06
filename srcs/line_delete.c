/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_delete.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saxiao <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/27 17:43:38 by saxiao            #+#    #+#             */
/*   Updated: 2018/11/06 21:51:24 by saxiao           ###   ########.fr       */
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
/*
static void	for_delect_key(void)
{
	write(1, " ", 1);
	tputs(tgetstr("le", 0), 1, my_putc);
	tputs(tgetstr("nd", 0), 1, my_putc);
}
*/

static int	remove_all(t_line *line)
{
//	int		i;
	/*
	move_nright(line);
	while (line->buf_len)
		delete_key(line);
		*/
		move_nleft(line);
		init_attr(BASIC_LINE_EDIT);
		write(STDOUT_FILENO, "\n", 1);
		init_attr(ADVANCED_LINE_EDIT);
		tputs(tgetstr("up", 0), 1, my_putc);
		tputs(tgetstr("cd", 0), 1, my_putc);
		print_prompt(line->prompt);
	//	i = line->start_po + 1;
//		while (--i)
//		tputs(tgetstr("nd", 0), 1, my_putc);

	//	if (ft_strstr((char *)l->buf, "\n"))
	//	tputs(tgetstr("up", 0), 1, my_putc);
	//	print_prompt(line->prompt);
	return (0);
}

#include <stdio.h>
int			delete_key(t_line *l)
{
	int		i;
	int		new_pos;

	if (l->pos > 0)
	{
		i = l->pos - 2;
		new_pos = l->pos - 1;
		remove_all(l);
		while (++i < l->buf_len)
			l->buf[i] = l->buf[i + 1];
	//	if (ft_strstr((char *)l->buf, "\n"))
	//	tputs(tgetstr("up", 0), 1, my_putc);
		i = 0;
		l->buf_len = 0;
		l->pos = 0;
		init_attr(ADVANCED_LINE_EDIT);
		while (l->buf[i])
			printable(l, l->buf[i++]);
		/*
		if ((l->buf_len + l->start_po) % l->line_max == (l->line_max - 1))
			for_delect_key();
		else
			tputs(tgetstr("dc", 0), 1, my_putc);
			*/
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
