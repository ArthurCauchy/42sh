/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/20 17:14:02 by acauchy           #+#    #+#             */
/*   Updated: 2017/11/21 09:20:24 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*usch_to_hex(unsigned char c)
{
	char			*hex;
	unsigned char	res;
	unsigned char	mod;
	size_t			i;

	hex = ft_strnew(2);
	res = c;
	mod = 0;
	i = 1;
	while (res != 0)
	{
		mod = res % 16;
		res /= 16;
		if (mod <= 9)
			hex[i] = '0' + mod;
		else
			hex[i] = 'a' - 10 + mod;
		--i;
	}
	return (hex);
}

void		ft_puthex_fd(unsigned char c, int fd)
{
	ft_putstr_fd(usch_to_hex(c), fd);
}
