/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exc_mark_get.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumenthi <lumenthi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 10:16:26 by lumenthi          #+#    #+#             */
/*   Updated: 2018/11/08 11:29:41 by lumenthi         ###   ########.fr       */
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
#include "exc_mark.h"

char	*get_digit(char *middle)
{
	char	*ret;

	ret = history_get(ft_atoi(middle) - 1);
	if (ret == NULL)
		return (exc_error(middle));
	return (ret);
}

char	*get_alpha(char *middle)
{
	int	i;
	int	tmp;
	int	biggest;
	int	ret;

	i = g_history->nb_lines - 1;
	biggest = 0;
	ret = -1;
	while (i >= 0)
	{
		tmp = check_matches(middle, g_history->line[i]);
		if (tmp > biggest)
		{
			biggest = tmp;
			ret = i;
		}
		i--;
	}
	if (ret > -1)
		return (ft_strdup(g_history->line[ret]));
	return (exc_error(middle));
}

char	*get_minus(char *middle)
{
	int		nb;
	char	*ret;

	if (ft_isdigit(middle[1]))
	{
		nb = ft_atoi(middle);
		nb = g_history->nb_lines + nb;
		ret = history_get(nb);
	}
	else if (ft_isalpha(middle[1]))
		ret = get_alpha(middle + 1);
	else
		return (exc_error(middle));
	if (ret == NULL)
		return (exc_error(middle));
	return (ret);
}

char	*get_exc(char *middle)
{
	char	*ret;

	ret = history_get(g_history->nb_lines - 1);
	if (ret == NULL)
		return (exc_error(middle));
	return (ret);
}

char	*get_inter(char *middle)
{
	int i;

	i = g_history->nb_lines - 1;
	while (i >= 0)
	{
		if (ft_strstr(g_history->line[i], (middle + 1)))
			return (ft_strdup(g_history->line[i]));
		i--;
	}
	return (exc_error(middle));
}
