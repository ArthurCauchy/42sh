/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 14:20:39 by acauchy           #+#    #+#             */
/*   Updated: 2017/11/22 10:09:55 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dst_len;
	size_t	src_len;
	long	available;
	size_t	bytes_to_copy;

	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	available = (long)size - (long)dst_len;
	bytes_to_copy = 0;
	if (dst_len >= size)
		return (src_len + size);
	if (available <= 0)
		return (dst_len + src_len);
	if (src_len > (size_t)available - 1)
		bytes_to_copy = (size_t)available - 1;
	else
		bytes_to_copy = src_len;
	ft_memcpy(dst + dst_len, src, bytes_to_copy);
	dst[dst_len + bytes_to_copy] = '\0';
	return (dst_len + src_len);
}
