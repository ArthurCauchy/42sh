/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_his_up_down.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saxiao <saxiao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/27 15:49:10 by saxiao            #+#    #+#             */
/*   Updated: 2018/09/14 13:28:31 by lumenthi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "line_edit.h"
#include "global.h"
#include "history.h"

int		history_up(t_line *line)
{
	int		i;
	int		max;
	char	*cmd;

	i = 0;
	max = g_history->nb_lines;
	if (line->buf_len)
		delete_all(line);
	if (g_history->nb_lines == 0)
		return (0);
	(g_history->position < max) ? g_history->position++ : 0;
	cmd = ft_strdup(g_history->line[max - g_history->position]);
	while (cmd[i])
	{
		put_a_key(line, cmd[i]);
		line->buf[i] = cmd[i];
		i++;
	}
	free(cmd);
	return (0);
}

int				history_down(t_line *line)
{
	int		i;
	int		max;
	char	*cmd;

	i = 0;
	max = g_history->nb_lines;
	if (line->buf_len)
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
	while (cmd[i])
	{
		put_a_key(line, cmd[i]);
		line->buf[i] = cmd[i];
		i++;
	}
	free(cmd);
	return (0);
}
