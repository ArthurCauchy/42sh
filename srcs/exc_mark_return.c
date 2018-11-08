/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exc_mark_return.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumenthi <lumenthi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 16:44:33 by lumenthi          #+#    #+#             */
/*   Updated: 2018/11/08 11:29:35 by lumenthi         ###   ########.fr       */
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

int		return_middle(char **middle, char *before)
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

char	*return_after(char *str, char **middle, int i)
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

char	*return_before(char *str, int i)
{
	char	*tmp;

	tmp = ft_strdup(str);
	tmp[i] = '\0';
	return (tmp);
}
