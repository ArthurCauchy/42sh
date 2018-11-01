/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saxiao <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/27 15:56:54 by saxiao            #+#    #+#             */
/*   Updated: 2018/10/22 12:24:32 by saxiao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "line_edit.h"

void	ft_freestrstr(char **str)
{
	char	**temp;

	if (str)
	{
		temp = str;
		while (*str)
		{
			free(*str);
			str++;
		}
		free(temp);
	}
}
