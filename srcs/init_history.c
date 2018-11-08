/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_history.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumenthi <lumenthi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 10:38:26 by lumenthi          #+#    #+#             */
/*   Updated: 2018/11/07 20:32:40 by lumenthi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "utils.h"
#include "history.h"
#include "global.h"

static int	size_error(void)
{
	ft_putendl_fd("42sh: invalid HISTSIZE value"
			", setting it to default (500)", 2);
	g_history->size = 500;
	return (0);
}

static char	**history_error(void)
{
	char **hist;

	if (!(hist = (char **)ft_memalloc(sizeof(char *) * (g_history->size + 1))))
		exit_error("malloc() error");
	return (hist);
}

static char	*home_error(void)
{
	ft_putstr_fd("no $HOME variable, history saved in /tmp\n", 2);
	return (ft_strjoin("/tmp", "/.42sh_history"));
}

static char	*get_home(t_env **env)
{
	char	*ret;
	char	*tmp;

	ret = NULL;
	if (!(tmp = read_from_env(env, "HOME")))
		return (home_error());
	ret = ft_strjoin(tmp, "/.42sh_history");
	free(tmp);
	return (ret);
}

int			init_history(t_env **env)
{
	if (!(g_history = malloc(sizeof(t_history))))
		exit_error("malloc() error");
	if (HISTSIZE <= 0)
		size_error();
	else
		g_history->size = HISTSIZE;
	g_history->histfile = get_home(env);
	g_history->nb_lines = 0;
	g_history->position = 0;
	g_history->index = 0;
	g_history->start_file = 0;
	if (!(g_history->line = history_read(g_history->histfile, 0)))
		g_history->line = history_error();
	g_history->nb_lines = args_size(g_history->line);
	g_history->start = args_size(g_history->line);
	return (1);
}
