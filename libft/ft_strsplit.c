/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 14:28:19 by acauchy           #+#    #+#             */
/*   Updated: 2017/11/20 14:39:36 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

/*
** Return how many valid words we have (valid if at least 1 char).
*/

static int	count_words(char const *s, char c)
{
	int		count;
	int		in_word;

	count = 0;
	in_word = 0;
	while (*s)
	{
		if (in_word == 0 && *s != c)
			in_word = 1;
		if (in_word == 1 && *s == c)
		{
			in_word = 0;
			++count;
		}
		++s;
	}
	if (in_word == 1)
		++count;
	return (count);
}

static int	copy_word(char **row, char const *cur, char *chunk_start)
{
	if (!(*row = (char*)malloc(cur - chunk_start + 1)))
		return (0);
	ft_memcpy(*row, chunk_start, cur - chunk_start);
	(*row)[cur - chunk_start] = '\0';
	return (1);
}

static int	fill_tab(char **tab, char const *s, char c)
{
	char	*chunk_start;
	int		in_word;
	size_t	i;

	in_word = 0;
	i = 0;
	chunk_start = (char*)s;
	while (1)
	{
		if (in_word == 0 && *s != c)
		{
			in_word = 1;
			chunk_start = (char*)s;
		}
		if (in_word == 1 && (*s == c || *s == '\0'))
		{
			in_word = 0;
			if (copy_word(&tab[i++], s, chunk_start) == 0)
				return (0);
		}
		if (*s == '\0')
			break ;
		++s;
	}
	return (i);
}

char		**ft_strsplit(char const *s, char c)
{
	char	**tab;
	int		words_count;

	if (!s)
		return (NULL);
	words_count = count_words(s, c);
	if (!(tab = (char**)malloc((words_count + 1) * sizeof(char*))))
		return (NULL);
	if (words_count > 0 && fill_tab(tab, s, c) == 0)
		return (NULL);
	tab[words_count] = 0;
	return (tab);
}
