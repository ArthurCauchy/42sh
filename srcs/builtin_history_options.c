/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_history_options.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumenthi <lumenthi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 11:42:32 by lumenthi          #+#    #+#             */
/*   Updated: 2018/11/08 11:53:05 by lumenthi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "utils.h"
#include "env.h"
#include "global.h"
#include "history.h"

int			history_d(char **args, int start)
{
	int	i;
	int	new;
	int	elem;

	if (!(args[start]))
		return (requires_error());
	if ((i = strchr_index(args[start], "0123456789")) ||
		ft_strcmp(args[start], "") == 0)
		return (del_error_alpha(i));
	elem = ft_atoi(args[start]);
	i = 0;
	new = (elem - g_history->index) - 1;
	if (g_history->nb_lines == g_history->size && new == -1)
		return (0);
	else if (new < 0 || new > (g_history->nb_lines - 1))
		return (del_error(elem));
	history_del(new);
	return (0);
}

int			history_r(char *file)
{
	char	**ta;
	int		i;

	i = 0;
	if (file == NULL || ft_strcmp(file, "") == 0)
		ta = history_read(g_history->histfile, 0);
	else
		ta = history_read(file, 0);
	if (ta == NULL)
		return (read_error(file));
	while (ta[i])
	{
		history_add(ta[i]);
		free(ta[i]);
		i++;
	}
	free(ta);
	return (0);
}

int			history_w(char *file)
{
	int ret;

	ret = 0;
	if (file == NULL || ft_strcmp(file, "") == 0)
	{
		ret = history_write_t(g_history->histfile, g_history->line);
		g_history->start = g_history->nb_lines;
	}
	else
		ret = history_write_t(file, g_history->line);
	return (ret = 1 ? 0 : 1);
}

int			history_p(char **args)
{
	int i;

	i = 2;
	if (args[i])
		history_del(g_history->nb_lines - 1);
	while (args[i])
		ft_putendl(args[i++]);
	return (0);
}

int			history_s(char **args)
{
	int		i;
	char	*str;

	i = 2;
	if (args[i])
	{
		history_del(g_history->nb_lines - 1);
		str = ft_strdup("");
		while (args[i])
		{
			str = ft_strjoinl(str, args[i++]);
			if (args[i])
				str = ft_strjoinl(str, " ");
		}
		history_add(str);
		free(str);
	}
	return (0);
}
