/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 19:02:33 by acauchy           #+#    #+#             */
/*   Updated: 2017/11/16 09:58:08 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	i;
	size_t	len;
	char	*s2;

	if (s && f)
	{
		i = 0;
		len = ft_strlen(s);
		if (!(s2 = (char*)malloc(len + 1)))
			return (NULL);
		while (i < len)
		{
			s2[i] = f(i, s[i]);
			++i;
		}
		s2[i] = '\0';
		return (s2);
	}
	return (NULL);
}
