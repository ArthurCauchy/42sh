/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumenthi <lumenthi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 15:14:56 by lumenthi          #+#    #+#             */
/*   Updated: 2018/11/07 20:33:43 by lumenthi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include "utils.h"
#include "global.h"
#include "history.h"

void		history_del(int elem)
{
	while (g_history->line[elem + 1])
	{
		free(g_history->line[elem]);
		g_history->line[elem] = ft_strdup(g_history->line[elem + 1]);
		elem++;
	}
	free(g_history->line[elem]);
	g_history->line[elem] = NULL;
	g_history->nb_lines--;
}

char		*history_get(int elem)
{
	char	*ret;

	if (elem < 0 || elem >= g_history->nb_lines)
		return (NULL);
	ret = ft_strdup(g_history->line[elem]);
	return (ret);
}

void		history_add(char *cmd)
{
	int size;

	size = args_size(g_history->line);
	if (size >= g_history->size)
	{
		tab_scroll(cmd);
		g_history->index += 1;
	}
	else
	{
		g_history->line[size] = ft_strdup(cmd);
		g_history->nb_lines++;
	}
	g_history->position = 0;
}
