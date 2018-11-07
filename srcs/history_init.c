/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumenthi <lumenthi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 15:00:56 by lumenthi          #+#    #+#             */
/*   Updated: 2018/11/07 20:33:30 by lumenthi         ###   ########.fr       */
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

static void	to_last_free(char **line, int i, char **tmp)
{
	*tmp = ft_strdup((*line) + i);
	free(*line);
	*line = ft_strdup(*tmp);
	free(*tmp);
}

void		to_last(char **line, int start)
{
	int		count;
	char	*tmp;
	int		nb_elem;
	int		i;

	count = 0;
	i = 0;
	while ((*line)[i] && count < start)
	{
		if ((*line)[i++] == '\n')
			count++;
	}
	nb_elem = get_elems(*line);
	if (nb_elem > g_history->size)
	{
		while ((*line)[i] && count < (nb_elem - g_history->size))
		{
			if ((*line)[i++] == '\n')
				count++;
		}
	}
	to_last_free(line, i, &tmp);
}

void		to_tab(char **line, char ***hist)
{
	int		i;
	char	*bn;
	char	*tmp;
	int		len;

	i = 0;
	tmp = ft_strdup(*line);
	while ((bn = ft_strchr(tmp, '\n')))
	{
		*bn = '\0';
		(*hist)[i] = ft_strndup(tmp, INPUT_MAX_LEN - 1);
		len = ft_strlen(tmp) + 1;
		free(tmp);
		tmp = ft_strdup((*line) + len);
		free(*line);
		*line = ft_strdup(tmp);
		i++;
	}
	(*hist)[i] = NULL;
	free(*line);
	free(tmp);
}

char		**history_read(char *filename, int start)
{
	char	*file;
	char	**hist;
	int		fd;

	if (!(hist = (char **)ft_memalloc(sizeof(char *) * (g_history->size + 1))))
		exit_error("malloc() error");
	fd = open(filename, O_RDONLY);
	if (fd > 0)
	{
		file = read_file(fd);
		if (ft_strcmp(filename, g_history->histfile) == 0)
			g_history->start_file = get_elems(file);
		to_last(&file, start);
		to_tab(&file, &hist);
		close(fd);
		return (hist);
	}
	free(hist);
	return (NULL);
}

void		tab_scroll(char *cmd)
{
	int		i;

	i = 0;
	while (g_history->line[i + 1])
	{
		free(g_history->line[i]);
		g_history->line[i] = ft_strdup(g_history->line[i + 1]);
		i++;
	}
	free(g_history->line[i]);
	g_history->line[i] = ft_strdup(cmd);
}
