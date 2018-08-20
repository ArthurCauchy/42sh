/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nbrlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/21 16:00:19 by acauchy           #+#    #+#             */
/*   Updated: 2017/12/21 16:55:37 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_nbrlen(long long nb)
{
	size_t	len;

	len = 0;
	if (nb < 0)
	{
		++len;
		nb *= -1;
	}
	else if (nb == 0)
		return (1);
	while (nb != 0)
	{
		nb = nb / 10;
		++len;
	}
	return (len);
}
