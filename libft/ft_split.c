/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saxiao <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/19 14:52:29 by saxiao            #+#    #+#             */
/*   Updated: 2018/01/31 15:28:00 by saxiao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static	int		check_include(char a, char *charset)
{
	while (*charset)
	{
		if (a == *charset)
			return (1);
		charset++;
	}
	return (0);
}

static	int		number_word(char *str, char *charset)
{
	int		i;

	i = 0;
	while (*str)
	{
		while (*str && check_include(*str, charset))
			str++;
		if (*str)
			i++;
		while (*str && !check_include(*str, charset))
			str++;
	}
	return (i);
}

char			**ft_split(char *str, char *charset)
{
	int		i;
	int		k;
	int		length;
	char	**result;

	i = -1;
	result = (char **)malloc(sizeof(char *) * (number_word(str, charset) + 1));
	while (*str)
	{
		while (*str && check_include(*str, charset))
			str++;
		if (!*str)
			break ;
		k = -1;
		length = 0;
		while (str[++k] && !check_include(str[k], charset))
			length++;
		result[++i] = malloc(sizeof(char) * (length + 1));
		k = -1;
		while (++k < length)
			result[i][k] = *str++;
		result[i][k] = '\0';
	}
	result[++i] = 0;
	return (result);
}
