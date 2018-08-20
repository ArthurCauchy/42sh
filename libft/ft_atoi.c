/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 10:49:24 by acauchy           #+#    #+#             */
/*   Updated: 2017/11/22 10:12:56 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** neg is a boolean, represented by a char so it takes less space in memory
*/

int	ft_atoi(const char *str)
{
	int					i;
	char				neg;
	unsigned long long	nbr;

	i = 0;
	neg = 0;
	nbr = 0;
	while (str[i] != '\0' && ft_isspace(str[i]))
		++i;
	if (str[i] != '\0' && (str[i] == '-' || str[i] == '+'))
		if (str[i++] == '-')
			neg = 1;
	while (str[i] != '\0' && ft_isdigit(str[i]))
	{
		nbr *= 10;
		nbr += str[i++] - 48;
	}
	if ((neg == 1 && nbr > 9223372036854775808UL)
			|| (neg == 0 && nbr > 9223372036854775807UL))
		return (neg == 1 ? 0 : -1);
	return (neg == 1 ? nbr * -1 : nbr);
}
