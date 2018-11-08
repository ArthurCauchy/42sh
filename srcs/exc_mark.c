/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exc_mark.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumenthi <lumenthi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/04 10:30:03 by lumenthi          #+#    #+#             */
/*   Updated: 2018/11/08 11:29:27 by lumenthi         ###   ########.fr       */
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

void		fill_inter(char *str, char **middle, int *i)
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

static void	set_null(char **before, char **middle, char **after)
{
	*before = NULL;
	*middle = NULL;
	*after = NULL;
}

static int	ft_mix(char **str, int *i)
{
	char	*before;
	char	*middle;
	char	*after;

	set_null(&before, &middle, &after);
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
