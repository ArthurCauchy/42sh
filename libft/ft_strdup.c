/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 09:35:29 by acauchy           #+#    #+#             */
/*   Updated: 2017/11/22 10:18:20 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>
#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*dst;

	if (!(dst = (char*)malloc((ft_strlen(s1) + 1) * sizeof(char))))
		return (NULL);
	ft_strcpy(dst, s1);
	return (dst);
}
