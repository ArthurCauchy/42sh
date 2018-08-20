/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 14:20:39 by acauchy           #+#    #+#             */
/*   Updated: 2017/11/22 10:09:44 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include "libft.h"

char	*ft_strcat(char *s1, const char *s2)
{
	if (!(ft_memcpy(s1 + ft_strlen(s1), s2, ft_strlen(s2) + 1)))
		return (NULL);
	return (s1);
}
