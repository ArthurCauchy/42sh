/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_history_helper.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumenthi <lumenthi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 11:49:28 by lumenthi          #+#    #+#             */
/*   Updated: 2018/11/08 11:52:20 by lumenthi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "utils.h"
#include "env.h"
#include "global.h"
#include "history.h"

int		strchr_index(char *str, char *index)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (ft_strchr_index(index, str[i]) == -1)
			return (str[i]);
		i++;
	}
	return (0);
}

char	*str_arg(char **args, int *start)
{
	char	*str;
	char	*tmp;
	int		i;

	str = ft_strdup("");
	while (args[*start] && args[*start][0] == '-')
	{
		i = 1;
		while (args[*start][i])
		{
			tmp = ft_strdup(str);
			free(str);
			str = ft_charjoin(tmp, args[*start][i]);
			free(tmp);
			i++;
		}
		(*start)++;
	}
	return (str);
}

int		spe_free(char **str)
{
	free(*str);
	return (1);
}

char	get_arg(char **args, int *start)
{
	char *str;

	if (args_size(args) == 1)
		return ('0');
	str = str_arg(args, start);
	if (*start == 1 && spe_free(&str))
		return ('0');
	if (!args_error(str))
		return (ret_char(&str));
	else if (spe_free(&str))
		return ('e');
	free(str);
	return ('0');
}

int		history_doclear(void)
{
	history_clear();
	return (1);
}
