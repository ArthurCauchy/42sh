/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 13:58:57 by acauchy           #+#    #+#             */
/*   Updated: 2017/11/16 10:08:09 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static char	*compute_real_start(char const *s, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		if ((!(ft_isspace(s[i]))) || i == len - 1)
			return ((char*)s + i);
		++i;
	}
	return ((char*)s);
}

static char	*compute_real_end(char const *s, size_t len, char *real_start)
{
	size_t	i;

	if (len == 0)
		i = 0;
	else
		i = len - 1;
	while (i > 0)
	{
		if ((!(ft_isspace(s[i]))) || s + i == real_start)
			return ((char*)s + i);
		--i;
	}
	return ((char*)s);
}

char		*ft_strtrim(char const *s)
{
	size_t	s_len;
	char	*real_start;
	char	*real_end;
	size_t	bytes_to_copy;
	char	*dst;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	real_start = compute_real_start(s, s_len);
	real_end = compute_real_end(s, s_len, real_start);
	bytes_to_copy = (real_end == real_start && ft_isspace(*real_start))
		? 0 : real_end - real_start + 1;
	if (!(dst = (char*)malloc(bytes_to_copy + 1)))
		return (NULL);
	ft_memcpy(dst, real_start, bytes_to_copy);
	dst[bytes_to_copy] = '\0';
	return (dst);
}
