/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_return_key.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saxiao <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/17 17:50:04 by saxiao            #+#    #+#             */
/*   Updated: 2018/11/13 11:55:41 by saxiao           ###   ########.fr       */
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

void	put_choice_end(t_line *line, int chioce_isdic)
{
	if (!last_letter_not_last_col(line))
		tputs(tgetstr("cd", 0), 1, my_putc);
	if (chioce_isdic)
		printable(line, '/');
	else
		printable(line, ' ');
}

int		return_key(t_line *line)
{
	line->auto_ct = -1;
	line->auto_last_choice_len = -1;
	move_nright(line);
	put_choice_end(line, line->auto_is_dic);
	if (nb_list(line->auto_lt) > 1)
		clear_auto_onscreen(line);
	move_nright(line);
	return (0);
}

void	clear_auto_onscreen(t_line *line)
{
	int		i;

	(void)line;
	init_attr(BASIC_LINE_EDIT);
	ft_printf("\n");
	init_attr(ADVANCED_LINE_EDIT);
	tputs(tgetstr("cd", 0), 1, my_putc);
	i = nb_line_command(line) + 1;
	while (--i)
		tputs(tgetstr("up", 0), 1, my_putc);
	i = line->start_po + 1;
	while (--i)
		tputs(tgetstr("nd", 0), 1, my_putc);
	line->pos = 0;
	move_nright(line);
	if (line->auto_lt)
		free_auto_lt(line);
}
