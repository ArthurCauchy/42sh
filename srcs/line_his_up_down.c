/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_his_up_down.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saxiao <saxiao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/27 15:49:10 by saxiao            #+#    #+#             */
/*   Updated: 2018/11/08 23:25:37 by saxiao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <curses.h>
#include <term.h>
#include "line_edit.h"
#include "global.h"
#include "history.h"
#include "ft_printf.h"

int			top_round(int nb, int dev)
{
	int		i;

	i = nb / dev;
	if (nb % dev)
		i++;
	return (i);
}

static int	help_2big_input(int *i, int *max, t_line *line)
{
	*i = 0;
	*max = g_history->nb_lines;
	if (top_round(line->buf_len + line->start_po, line->line_max) > \
			line->screen_height)
	{
		tputs(tgetstr("cl", 0), 1, my_putc);
		print_prompt(line->prompt);
		return (1);
	}
	return (0);
}

static void	put_history(t_line *line, char *cmd, int index)
{
	while (cmd[index])
	{
		put_a_key(line, cmd[index]);
		line->buf[index] = cmd[index];
		index++;
	}
}

int			history_up(t_line *line)
{
	int		i;
	int		max;
	char	*cmd;

	if (!help_2big_input(&i, &max, line) && line->buf_len)
		delete_all(line);
	if (g_history->nb_lines == 0)
		return (0);
	(g_history->position < max) ? g_history->position++ : 0;
	cmd = ft_strdup(g_history->line[max - g_history->position]);
	put_history(line, cmd, i);
	free(cmd);
	return (0);
}

int			history_down(t_line *line)
{
	int		i;
	int		max;
	char	*cmd;

	if (!help_2big_input(&i, &max, line) && line->buf_len)
		delete_all(line);
	if (g_history->position > 1)
		g_history->position--;
	else if (g_history->position == 1)
	{
		g_history->position--;
		return (0);
	}
	else
		return (0);
	cmd = ft_strdup(g_history->line[max - g_history->position]);
	put_history(line, cmd, i);
	free(cmd);
	return (0);
}
