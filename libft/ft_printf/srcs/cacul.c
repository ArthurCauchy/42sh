/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cacul.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saxiao <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/21 18:50:56 by saxiao            #+#    #+#             */
/*   Updated: 2017/12/22 06:15:37 by saxiao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <wchar.h>
#include "../../libft.h"
#include "../includes/ft_printf.h"

int			nb_digit(char *str)
{
	int		i;

	i = 0;
	while ('0' <= *str && *str <= '9')
	{
		i++;
		str++;
	}
	return (i);
}

int			max_3(int x, int y, int z)
{
	int		max;

	max = x;
	if (y > max)
		max = y;
	if (z > max)
		max = z;
	return (max);
}

int			max_2(int x, int y)
{
	if (x > y)
		return (x);
	return (y);
}

static void	we_to_char(wchar_t we, char *c)
{
	if (we <= 0x7f)
		c[0] = we;
	else if (we <= 0x7ff)
	{
		c[0] = (we >> 6) + 192;
		c[1] = (we & 63) + 128;
	}
	else if (we <= 0xffff)
	{
		c[0] = (we >> 12) + 224;
		c[1] = (we >> 6) + 192;
		c[2] = (we & 63) + 128;
	}
	else if (we <= 0x1fffff)
	{
		c[0] = (we >> 18) + 240;
		c[1] = (we >> 12) + 224;
		c[2] = (we >> 6) + 192;
		c[3] = (we & 63) + 128;
	}
}

void		ft_putwchar(wchar_t we)
{
	char	c[5];

	ft_bzero(c, 5);
	we_to_char(we, c);
	write(1, c, ft_strlen(c));
}
