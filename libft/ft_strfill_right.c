/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strfill_right.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 20:09:19 by acauchy           #+#    #+#             */
/*   Updated: 2018/01/11 16:19:25 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strfill_right(char const *s, size_t size, char fill_char)
{
	char	*dst;
	size_t	i;
	size_t	padd_size;

	if (!(dst = (char*)malloc(size + 1)))
		return (NULL);
	i = 0;
	if (size >= ft_strlen(s))
		padd_size = size - ft_strlen(s);
	else
		padd_size = 0;
	while (i < padd_size)
	{
		dst[i] = fill_char;
		++i;
	}
	while (i < size)
	{
		dst[i] = s[i - padd_size];
		++i;
	}
	dst[size] = '\0';
	return (dst);
}
