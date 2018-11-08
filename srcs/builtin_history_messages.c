/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_history_messages.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumenthi <lumenthi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 11:46:00 by lumenthi          #+#    #+#             */
/*   Updated: 2018/11/08 11:49:08 by lumenthi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "utils.h"
#include "env.h"
#include "global.h"
#include "history.h"

int		multiple_afile(void)
{
	ft_putendl_fd("history: cannot use more than one of -anrw", 2);
	return (1);
}

int		args_error(char *str)
{
	int		i;
	int		count;
	char	c;

	i = 0;
	count = 0;
	if (((c = strchr_index(str, "cdanrwps")) > 0) && history_usage(c))
		return (1);
	if (strchr_index(str, "cdps") == 0)
		return (0);
	while (str[i])
	{
		if (ft_strchr_index("anrw", str[i]) != -1)
			count++;
		i++;
	}
	if (count > 1)
		return (multiple_afile());
	return (0);
}

int		history_too_much(void)
{
	ft_putendl_fd("history: too many arguments", 2);
	return (1);
}

int		history_numeric(void)
{
	ft_putendl_fd("history: numeric argument required", 2);
	return (1);
}

int		print_nhistory(int nb)
{
	int i;
	int start;

	i = 0;
	start = g_history->nb_lines - nb;
	if (g_history->nb_lines <= 0)
		return (1);
	while (g_history->line[i])
	{
		if (i >= start)
		{
			ft_putnbr((i + 1) + g_history->index);
			ft_putstr(" - [");
			ft_putstr(g_history->line[i]);
			ft_putendl("]");
		}
		i++;
	}
	return (0);
}
