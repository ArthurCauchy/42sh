/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 09:35:29 by acauchy           #+#    #+#             */
/*   Updated: 2018/06/03 12:55:24 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>
#include "libft.h"

char	*ft_strdup_free(char *s1)
{
	char	*dst;

	if (!(dst = (char*)malloc((ft_strlen(s1) + 1) * sizeof(char))))
		return (NULL);
	ft_strcpy(dst, s1);
	free(s1);
	return (dst);
}
