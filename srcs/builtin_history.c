/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_history.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 10:06:00 by acauchy           #+#    #+#             */
/*   Updated: 2018/11/10 12:23:24 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "utils.h"
#include "env.h"
#include "global.h"
#include "history.h"

int			history_a(char *file)
{
	return (history_write_a(file));
}

int			history_n(char *file)
{
	char	**add;
	int		i;

	i = 0;
	if (file == NULL || ft_strcmp(file, "") == 0)
		add = history_read(g_history->histfile, g_history->start_file);
	else
		add = history_read(file, g_history->start_file);
	if (add == NULL)
		return (1);
	while (add[i])
	{
		history_add(add[i]);
		free(add[i]);
		i++;
	}
	free(add);
	return (0);
}

char		ret_char(char **str)
{
	if (ft_strchr(*str, 'c') && spe_free(str))
		return ('c');
	else if (ft_strchr(*str, 'd') && spe_free(str))
		return ('d');
	else if (ft_strchr(*str, 's') && spe_free(str))
		return ('s');
	else if (ft_strchr(*str, 'p') && spe_free(str))
		return ('p');
	else if (ft_strchr(*str, 'a') && spe_free(str))
		return ('a');
	else if (ft_strchr(*str, 'n') && spe_free(str))
		return ('n');
	else if (ft_strchr(*str, 'r') && spe_free(str))
		return ('r');
	else if (ft_strchr(*str, 'w') && spe_free(str))
		return ('w');
	return ('0');
}

int			history_base(char **args, int start)
{
	int		i;

	i = 0;
	if (args[start] == NULL)
		return (print_nhistory(g_history->nb_lines));
	else
	{
		while (args[start + i])
		{
			if (strchr_index(args[start + i], "0123456789") ||
				ft_strcmp(args[start + i], "") == 0)
				return (history_numeric());
			i++;
		}
		if (i > 1)
			return (history_too_much());
		return (print_nhistory(ft_atoi(args[start])));
	}
}

int			builtin_history(t_env **env, char **args)
{
	int		start;
	char	arg;

	(void)env;
	start = 1;
	arg = get_arg(args, &start);
	if (arg == '0')
		return (history_base(args, start));
	else if (arg == 'c')
		return (-history_doclear());
	else if (arg == 'r')
		return (-history_r(args[start]));
	else if (arg == 'a')
		return (-history_a(args[start]));
	else if (arg == 'n')
		return (-history_n(args[start]));
	else if (arg == 'w')
		return (-history_w(args[start]));
	else if (arg == 'p')
		return (-history_p(args));
	else if (arg == 's')
		return (-history_s(args));
	else if (arg == 'd')
		return (-history_d(args, start));
	return (0);
}
