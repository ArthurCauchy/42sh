/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_key_isarrow.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saxiao <saxiao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/17 15:10:24 by saxiao            #+#    #+#             */
/*   Updated: 2018/11/09 18:13:00 by acauchy          ###   ########.fr       */
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

static void	auto_arrow_left(t_line *line, int real_nb_line)
{
	if (line->auto_ct % nb_list(line->auto_lt) / real_nb_line != 0)
		line->auto_ct = line->auto_ct - real_nb_line;
	else
	{
		if (line->auto_ct % nb_list(line->auto_lt) % real_nb_line + \
				(line->w.col - 1) * real_nb_line < nb_list(line->auto_lt))
			line->auto_ct = line->auto_ct + (line->w.col - 1) * real_nb_line;
		else
			line->auto_ct = line->auto_ct + (line->w.col - 2) * real_nb_line;
	}
}

static void	auto_arrow_right(t_line *line, int real_nb_line)
{
	if (line->auto_ct % nb_list(line->auto_lt) + real_nb_line \
			< nb_list(line->auto_lt))
		line->auto_ct = line->auto_ct + real_nb_line;
	else
		line->auto_ct = line->auto_ct % nb_list(line->auto_lt) % real_nb_line;
}

static void	auto_arrow_up(t_line *line, int real_line)
{
	if (line->auto_ct % nb_list(line->auto_lt) % real_line == 0)
	{
		if (line->auto_ct % nb_list(line->auto_lt) + real_line + 1 \
				> nb_list(line->auto_lt))
			line->auto_ct = nb_list(line->auto_lt) - 2;
		else
			line->auto_ct = line->auto_ct % nb_list(line->auto_lt) + \
							real_line - 1;
	}
	else
		line->auto_ct--;
}

static void	auto_arrow_down(t_line *line, int real_nb_line)
{
	if (line->auto_ct % nb_list(line->auto_lt) == nb_list(line->auto_lt) - 1 \
			|| line->auto_ct % nb_list(line->auto_lt) % real_nb_line \
			== real_nb_line - 1)
		line->auto_ct = line->auto_ct - \
						line->auto_ct % nb_list(line->auto_lt) % real_nb_line;
	else
		line->auto_ct++;
}

int			arrow_keys_in_autoline(t_line *line, t_env **env, unsigned long key)
{
	int		real_nb_line;

	real_nb_line = nb_list(line->auto_lt) / line->w.col;
	if (nb_list(line->auto_lt) % line->w.col)
		real_nb_line++;
	line->auto_ct--;
	if (key == ARROW_LEFT)
		auto_arrow_left(line, real_nb_line);
	else if (key == ARROW_RIGHT)
		auto_arrow_right(line, real_nb_line);
	else if (key == ARROW_UP)
		auto_arrow_up(line, real_nb_line);
	else if (key == ARROW_DOWN)
		auto_arrow_down(line, real_nb_line);
	my_tabkey(line, env);
	line->is_tabb4 = 1;
	return (0);
}
