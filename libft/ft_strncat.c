/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 14:20:39 by acauchy           #+#    #+#             */
/*   Updated: 2017/11/22 10:09:39 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include "libft.h"

char	*ft_strncat(char *s1, const char *s2, size_t n)
{
	size_t	s1_len;
	size_t	s2_len;
	size_t	bytes_to_copy;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	if (n > s2_len)
		bytes_to_copy = s2_len;
	else
		bytes_to_copy = n;
	ft_memcpy(s1 + s1_len, s2, bytes_to_copy);
	s1[s1_len + bytes_to_copy] = '\0';
	return (s1);
}
