/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_history.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumenthi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 10:38:26 by lumenthi          #+#    #+#             */
/*   Updated: 2018/09/01 18:55:23 by lumenthi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "utils.h"
#include "history.h"
#include "global.h"

static int  size_error(void)
{
	ft_putendl_fd("42sh: invalid HISTSIZE value, setting it to default (500)", 2);
	g_history->SIZE = 500;
	return (0);
}

static char             **history_error(void)
{
	char **hist;

	if (!(hist = (char **)ft_memalloc(sizeof(char *) * (g_history->SIZE + 1))))
		exit_error("malloc() error");
	ft_putstr_fd("42sh: cant read from ", 2);
	ft_putendl_fd(HISTFILE, 2);
	return (hist);
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
