/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_multifree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 14:22:10 by acauchy           #+#    #+#             */
/*   Updated: 2018/02/22 14:31:37 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	ft_multifree(int nbargs, ...)
{
	va_list	valist;
	int		i;

	va_start(valist, nbargs);
	i = 0;
	while (i < nbargs)
	{
		free(va_arg(valist, void*));
		++i;
	}
	va_end(valist);
}
