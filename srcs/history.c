/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumenthi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 10:38:26 by lumenthi          #+#    #+#             */
/*   Updated: 2018/09/01 18:55:23 by lumenthi         ###   ########.fr       */
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

static char		*read_file(int fd)
{
	char	*line;
	char	buf[2];
	int		ret;

	line = ft_strdup("");
	while ((ret = read(fd, buf, 1)))
	{
		buf[ret] = '\0';
		line = ft_strjoinl(line, buf);
	}
	return (line);
}

static int		get_elems(char *line)
{
	int		count;
	int		i;

	count = 0;
	i = 0;
	while (line[i])
	{
		if (line[i++] == '\n')
			count++;
	}
	return (count);
}

static void		to_last(char **line, int start)
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
	if (nb_elem > g_history->SIZE)
	{
		while ((*line)[i] && count < (nb_elem - g_history->SIZE))
		{
			if ((*line)[i++] == '\n')
				count++;
		}
	}
	tmp = ft_strdup((*line) + i);
	free(*line);
	*line = ft_strdup(tmp);
	free(tmp);
}

static void		to_tab(char **line, char ***hist)
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
		(*hist)[i] = ft_strdup(tmp);
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

static void		hist_null(char ***hist)
{
	int i;

	i = 0;
	while (i <= g_history->SIZE)
	{
		(*hist)[i] = NULL;
		i++;
	}
}

char		**history_read(char *filename, int start)
{
	char	*file;
	char	**hist;
	int		fd;

	if (!(hist = (char **)malloc(sizeof(char *) * (g_history->SIZE + 1))))
		exit_error("malloc() error");
	hist_null(&hist);
	fd = open(filename, O_RDONLY);
	if (fd > 0)
	{
		file = read_file(fd);
		if (ft_strcmp(filename, HISTFILE) == 0)
			g_history->start_file = get_elems(file);
		to_last(&file, start);
		to_tab(&file, &hist);
		close(fd);
		return (hist);
	}
	free(hist);
	return (NULL);
}

static void	tab_scroll(char *cmd)
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
	return (ft_strdup(g_history->line[elem]));
}

void		history_add(char *cmd)
{
	int size;

	size = args_size(g_history->line);
	if (size >= g_history->SIZE)
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

static char	*to_string(char **ar)
{
	char	*line;
	int		i;

	i = 0;
	line = ft_strdup("");
	while (ar[i])
	{
		line = ft_strjoinl(line, ar[i]);
		line = ft_strjoinl(line, "\n");
		i++;
	}
	return (line);
}

static int			h_append(char *file, char **hist)
{
	int		fd;
	char	*hist_string;

	fd = open(file, O_RDWR|O_APPEND|O_CREAT, 0644);
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

int			history_writeA(char *file)
{
	int		i;
	int		ret;

	i = 0;
	ret = 0;
	while ((i + g_history->index) < g_history->start && g_history->line[i])
		i++;
	if (file == NULL || ft_strcmp(file, "") == 0)
	{
		ret = h_append(HISTFILE, g_history->line + i);
		g_history->start = g_history->nb_lines;
	}
	else
		ret = h_append(file, g_history->line + i);
	return (ret = 1 ? 0 : 1);
}

int			history_writeT(char *file, char **hist)
{
	int		fd;
	char	*hist_string;

	fd = open(file, O_RDWR|O_TRUNC|O_CREAT, 0644);
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
	g_history->history_writeA(HISTFILE);
	g_history->history_clear();
	free(g_history);
}

static char		**history_error(void)
{
	char **hist;

	if (!(hist = (char **)malloc(sizeof(char *) * (g_history->SIZE + 1))))
		exit_error("malloc() error");
	hist_null(&hist);
	ft_putstr_fd("42sh: cant read from ", 2);
	ft_putendl_fd(HISTFILE, 2);
	return (hist);
}

static int	size_error(void)
{
	ft_putendl_fd("42sh: invalid HISTSIZE value, setting it to default (500)", 2);
	g_history->SIZE = 500;
	return (0);
}

int			init_history(void)
{
	if (!(g_history = malloc(sizeof(t_history))))
		exit_error("malloc() error");
	if (HISTSIZE <= 0)
		size_error();
	else
		g_history->SIZE = HISTSIZE;
	g_history->nb_lines = 0;
	g_history->position = 0;
	g_history->index = 0;
	g_history->start_file = 0;
	g_history->history_add = history_add;
	g_history->history_get = history_get;
	g_history->history_read = history_read;
	g_history->history_exit = history_exit;
	g_history->history_clear = history_clear;
	g_history->history_del = history_del;
	g_history->history_writeA = history_writeA;
	g_history->history_writeT = history_writeT;
	if (!(g_history->line = history_read(HISTFILE, 0)))
		g_history->line = history_error();
	g_history->nb_lines = args_size(g_history->line);
	g_history->start  = args_size(g_history->line);
	return (1);
}
