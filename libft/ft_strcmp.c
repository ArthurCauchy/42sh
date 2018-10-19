/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 11:26:57 by acauchy           #+#    #+#             */
/*   Updated: 2018/10/18 14:30:28 by saxiao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	if (s1 && s2)
	{
	while ((unsigned char)s1[i] == (unsigned char)s2[i] && s1[i] && s2[i])
		++i;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	}
	return (1);
}
