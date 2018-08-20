/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 10:39:33 by acauchy           #+#    #+#             */
/*   Updated: 2017/11/22 10:08:05 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*cur;
	unsigned char	ch;

	i = 0;
	cur = (unsigned char*)s;
	ch = (unsigned char)c;
	while (i < n)
	{
		if (cur[i] == ch)
			return (cur + i);
		++i;
	}
	return (0);
}
