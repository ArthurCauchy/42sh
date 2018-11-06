/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exc_mark.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumenthi <lumenthi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/04 10:30:03 by lumenthi          #+#    #+#             */
/*   Updated: 2018/11/06 16:57:02 by lumenthi         ###   ########.fr       */
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

static void	fill_inter(char *str, char **middle, int *i)
{
	int j;

	j = 1;
	(*i)++;
	if (str[*i])
	{
		(*middle)[0] = '?';
		while (!(ft_isspace(str[*i])) && str[*i])
			(*middle)[j++] = str[(*i)++];
	}
	else
		(*middle)[0] = '?';
	(*middle)[j] = '\0';
}

static char	*get_digit(char *middle)
{
	char	*ret;

	ret = history_get(ft_atoi(middle) - 1);
	if (ret == NULL)
		return (exc_error(middle));
	return (ret);
}

static char	*get_alpha(char *middle)
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

static char	*get_minus(char *middle)
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

static char	*get_exc(char *middle)
{
	char	*ret;

	ret = history_get(g_history->nb_lines - 1);
	if (ret == NULL)
		return (exc_error(middle));
	return (ret);
}

static char	*get_inter(char *middle)
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

static int	ft_mix(char **str, int *i)
{
	char	*before;
	char	*middle;
	char	*after;

	before = NULL;
	middle = NULL;
	after = NULL;
	before = return_before(*str, *i);
	after = return_after(*str, &middle, *i);
	if (!(return_middle(&middle, before)))
	{
		free(*str);
		*str = ft_strdup("");
		free(before);
		free(middle);
		free(after);
		return (1);
	}
	free(*str);
	*str = ft_add(before, middle, after);
	free(before);
	free(middle);
	free(after);
	return (0);
}

int			exc_mark(char **str)
{
	int		i;
	int		mark;

	i = 0;
	mark = 0;
	while ((*str)[i])
	{
		if ((*str)[i] == '!' && is_legit(*str, i))
		{
			if ((ft_mix(str, &i)))
				return (1);
			if (i + 1 > (int)ft_strlen(*str))
				break ;
			mark = 1;
		}
		i++;
	}
	if (mark)
		ft_putendl(*str);
	return (1);
}
