/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 10:39:33 by acauchy           #+#    #+#             */
/*   Updated: 2018/02/21 14:35:37 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t			i;
	size_t			len;

	i = 0;
	len = ft_strlen(s);
	while (i < len + 1)
	{
		if (s[i] == c)
			return ((char*)s + i);
		++i;
	}
	return (0);
}
