/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 09:36:20 by acauchy           #+#    #+#             */
/*   Updated: 2017/11/20 15:57:57 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"
#include <stdio.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*s1_ptr;
	unsigned char	*s2_ptr;

	if (n == 0)
		return (0);
	i = 0;
	s1_ptr = (unsigned char*)s1;
	s2_ptr = (unsigned char*)s2;
	while (i < n && s1_ptr[i] == s2_ptr[i])
		++i;
	if (i == n)
		return (0);
	return ((int)s1_ptr[i] - (int)s2_ptr[i]);
}
