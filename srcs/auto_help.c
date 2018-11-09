/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_auto_complet.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saxiao <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/17 15:05:59 by saxiao            #+#    #+#             */
/*   Updated: 2018/11/08 23:40:00 by saxiao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <curses.h>
#include <term.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include "ft_printf.h"
#include "line_edit.h"
#include "global.h"

int			last_letter_not_last_col(t_line *line)
{
	int		i;
	int		j;

	i = line->buf_len - 1;
	j = 0;
	while (i >= 0)
	{
		if (line->buf[i] == '\n')
			return (j % line->line_max);
		j++;
		i--;
	}
	return ((line->buf_len + line->start_po) % line->line_max);
}

int			not_last_letter(t_line *line)
{
	int		i;

	if ((i = newline_b4(line, line->pos + 1)))
		return (i % line->line_max);
	return ((line->pos + 1 + line->start_po) % line->line_max);
}

void		for_put_a_key(t_line *line, unsigned long key)
{
	(void)key;
	(void)line;
	write(STDOUT_FILENO, &key, 1);
	if (key == '\n')
		tputs(tgetstr("cr", 0), 1, my_putc);
}
