/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumenthi <lumenthi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 10:38:26 by lumenthi          #+#    #+#             */
/*   Updated: 2018/11/07 20:30:09 by lumenthi         ###   ########.fr       */
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

static int	h_append(char *file, char **hist)
{
	int		fd;
	char	*hist_string;

	fd = open(file, O_RDWR | O_APPEND | O_CREAT, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("42sh: cant write to ", 2);
		ft_putstr_fd(file, 2);
		ft_putendl_fd(", history not saved", 2);
		return (0);
	}
	hist_string = to_string(hist);
	write(fd, hist_string, ft_strlen(hist_string));
	free(hist_string);
	close(fd);
	return (1);
}

int			history_write_a(char *file)
{
	int		i;
	int		ret;

	i = 0;
	ret = 0;
	while ((i + g_history->index) < g_history->start && g_history->line[i])
		i++;
	if (file == NULL || ft_strcmp(file, "") == 0)
	{
		ret = h_append(g_history->histfile, g_history->line + i);
		g_history->start = g_history->nb_lines;
	}
	else
		ret = h_append(file, g_history->line + i);
	return (ret = 1 ? 0 : 1);
}

int			history_write_t(char *file, char **hist)
{
	int		fd;
	char	*hist_string;

	fd = open(file, O_RDWR | O_TRUNC | O_CREAT, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("42sh: cant write to ", 2);
		ft_putstr_fd(file, 2);
		ft_putendl_fd(", history not saved", 2);
		return (0);
	}
	hist_string = to_string(hist);
	write(fd, hist_string, ft_strlen(hist_string));
	free(hist_string);
	close(fd);
	return (1);
}

void		history_clear(void)
{
	int i;

	i = 0;
	while (g_history->line[i])
		free(g_history->line[i++]);
	hist_null(&g_history->line);
	g_history->index = 0;
	g_history->nb_lines = 0;
	g_history->start = 1;
}

void		history_exit(void)
{
	history_write_a(g_history->histfile);
	history_clear();
	free(g_history->histfile);
	free(g_history->line);
	free(g_history);
}
