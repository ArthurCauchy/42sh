/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 11:08:48 by acauchy           #+#    #+#             */
/*   Updated: 2017/11/22 10:37:14 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include "libft.h"

int	ft_swap(void **ptr1, void **ptr2, size_t size1, size_t size2)
{
	void	*tmp;

	if (ptr1 && !*ptr1)
		tmp = NULL;
	if (!ptr1 || !ptr2 || (*ptr1 && !(tmp = malloc(size1))))
		return (-1);
	ft_memcpy(tmp, *ptr1, size1);
	free(*ptr1);
	if (*ptr2 && (*ptr1 = malloc(size2)))
		*ptr1 = ft_memcpy(*ptr1, *ptr2, size2);
	else
		*ptr1 = NULL;
	free(*ptr2);
	if (tmp && (*ptr2 = malloc(size1)))
		*ptr2 = ft_memcpy(*ptr2, tmp, size1);
	else
		*ptr2 = NULL;
	return (0);
}
