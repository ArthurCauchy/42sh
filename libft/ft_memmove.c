/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 19:18:03 by acauchy           #+#    #+#             */
/*   Updated: 2017/11/22 10:07:56 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>
#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t			i;
	unsigned char	*ptr_dst;
	unsigned char	*buf;

	i = 0;
	ptr_dst = (unsigned char*)dst;
	if (!(buf = (unsigned char*)malloc(sizeof(unsigned char) * len)))
		return (dst);
	ft_memcpy((void*)buf, src, len);
	while (i < len)
	{
		ptr_dst[i] = buf[i];
		++i;
	}
	return (dst);
}
