/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 09:35:29 by acauchy           #+#    #+#             */
/*   Updated: 2018/09/11 16:46:27 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>
#include "libft.h"

char	*ft_strndup(const char *s1, size_t n)
{
	char	*dst;

	if (!(dst = (char*)malloc((n + 1) * sizeof(char))))
		return (NULL);
	ft_strncpy(dst, s1, n);
	dst[n] = '\0';
	return (dst);
}
