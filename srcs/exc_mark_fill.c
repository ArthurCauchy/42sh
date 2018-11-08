/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exc_mark_fill.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumenthi <lumenthi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 16:47:16 by lumenthi          #+#    #+#             */
/*   Updated: 2018/11/08 11:30:21 by lumenthi         ###   ########.fr       */
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

void	fill_digit(char *str, char **middle, int *i)
{
	int j;

	j = 0;
	while (ft_isdigit(str[*i]) && str[*i])
	{
		(*middle)[j] = str[*i];
		j++;
		(*i)++;
	}
	(*middle)[j] = '\0';
}

void	fill_alpha(char *str, char **middle, int *i)
{
	int j;

	j = 0;
	while (ft_isalpha(str[*i]) && str[*i])
	{
		(*middle)[j] = str[*i];
		j++;
		(*i)++;
	}
	(*middle)[j] = '\0';
}

void	fill_other(char *str, char **middle, int *i)
{
	int j;

	j = 0;
	while (!ft_isspace(str[*i]) && str[*i])
	{
		(*middle)[j] = str[*i];
		j++;
		(*i)++;
	}
	(*middle)[j] = '\0';
}

void	fill_one(char *str, char **middle, int *i)
{
	int j;

	j = 0;
	while (j < 1 && str[*i])
	{
		(*middle)[j] = str[*i];
		j++;
		(*i)++;
	}
	(*middle)[j] = '\0';
}

void	fill_minus(char *str, char **middle, int *i)
{
	int j;

	j = 1;
	(*i)++;
	if (str[*i])
	{
		(*middle)[0] = '-';
		if (ft_isdigit(str[*i]))
		{
			while ((ft_isdigit(str[*i]) || ft_isalpha(str[*i])) && str[*i])
				(*middle)[j++] = str[(*i)++];
		}
		else
		{
			while (!(ft_isspace(str[*i])) && str[*i])
				(*middle)[j++] = str[(*i)++];
		}
	}
	else
		(*middle)[0] = '-';
	(*middle)[j] = '\0';
}
