/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exc_mark.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumenthi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/04 10:30:03 by lumenthi          #+#    #+#             */
/*   Updated: 2018/09/10 16:00:03 by acauchy          ###   ########.fr       */
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

static char	*return_before(char *str, int i)
{
	char	*tmp;

	tmp = ft_strdup(str);
	tmp[i] = '\0';
	return (tmp);
}

static void	fill_digit(char *str, char **middle, int *i)
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

static void	fill_alpha(char *str, char **middle, int *i)
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

static void	fill_one(char *str, char **middle, int *i)
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

static void fill_minus(char *str, char **middle, int *i)
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

static void	fill_other(char *str, char **middle, int *i)
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

static char	*exc_error(char *str)
{
	ft_putchar_fd('!', 2);
	ft_putstr_fd(str, 2);
	ft_putendl_fd(": event not found", 2);
	return (NULL);
}

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

static char	*return_after(char *str, char **middle, int i)
{
	i++;
	*middle = (char *)malloc(sizeof(char) * (ft_strlen(str + i) + 1));
	if (ft_isdigit(str[i]))
		fill_digit(str, middle, &i);
	else if (ft_isalpha(str[i]))
		fill_alpha(str, middle, &i);
	else if (str[i] == '#' || str[i] == '!')
		fill_one(str, middle, &i);
	else if (str[i] == '-')
		fill_minus(str, middle, &i);
	else if (str[i] == '?')
		fill_inter(str, middle, &i);
	else
		fill_other(str, middle, &i);
	return (ft_strdup(str + i));
}

static char	*get_digit(char *middle)
{
	char	*ret;

	ret = history_get(ft_atoi(middle) - 1);
	if (ret == NULL)
		return (exc_error(middle));
	return (ret);
}

static int	check_matches(char *str1, char *str2)
{
	int i;
	i = 0;
	
	while (str1[i] && str2[i] && str1[i] == str2[i])
		i++;
	if (i == (int)ft_strlen(str1))
		return (i);
	else
		return (0);
}

static char *get_alpha(char *middle)
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

static int	return_middle(char **middle, char *before)
{
	char	*value;

	if (ft_isdigit((*middle)[0]))
		value = get_digit(*middle);
	else if (ft_isalpha((*middle)[0]))
		value = get_alpha(*middle);
	else if ((*middle)[0] == '#')
		value = ft_strdup(before);
	else if ((*middle)[0] == '-')
		value = get_minus(*middle);
	else if ((*middle)[0] == '!')
		value = get_exc(*middle);
	else if ((*middle)[0] == '?')
		value = get_inter(*middle);
	else
	{
		exc_error(*middle);
		return (0);
	}
	if (value == NULL)
		return (0);
	free(*middle);
	*middle = ft_strdup(value);
	free(value);
	return (1);
}

static char	*ft_add(char *before, char *middle, char *after)
{
	char	*ret;
	char	*tmp;

	tmp = ft_strjoin(before, middle);
	ret = ft_strjoin(tmp, after);
	free(tmp);
	return (ret);
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

static int	is_backslash(char *str, int pos, int s_quote)
{
	int	ret;
	int	i;

	i = pos;
	while (str[i] && str[i - 1] == 92)
		i--;
	ret = pos - i;
	if (ret % 2 == 1 && !s_quote)
		return (1);
	return (0);
}

static int	is_legit(char *str, int pos)
{
	int	i;
	int	s_quote;

	s_quote = 0;
	i = 0;
	while (i < pos && str[i])
	{
		if (str[i] == 39 && !is_backslash(str, i, s_quote))
			s_quote = (s_quote == 0) ? 1 : 0;
		i++;
	}
	if (s_quote == 1 || (pos - 1 > 0 && str[pos - 1] && str[pos - 1] == 92))
		return (0);
	return (1);
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
			if (i+1 > (int)ft_strlen(*str))
				break;
			mark = 1;
		}
		i++;
	}
	if (mark)
		ft_putendl(*str);
	return (1);
}
