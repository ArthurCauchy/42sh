/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa_max.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saxiao <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/21 22:37:09 by saxiao            #+#    #+#             */
/*   Updated: 2017/12/22 02:49:32 by saxiao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdint.h>
#include "../../libft.h"
#include "../includes/ft_printf.h"

static	int	nb_dg_short(intmax_t n)
{
	int			i;
	uintmax_t	nb;

	i = 1;
	if (n < 0)
	{
		i = 2;
		nb = (uintmax_t)n * -1;
	}
	else
		nb = (uintmax_t)n;
	while (nb > 9)
	{
		i++;
		nb = nb / 10;
	}
	return (i);
}

char		*ft_itoa_short(short n)
{
	char			*number;
	int				len;
	unsigned short	cp_n;

	len = nb_dg_short(n);
	if (!(number = (char *)malloc(len + 1)))
		return (NULL);
	number[len] = '\0';
	if (!n)
		number[0] = '0';
	if (n < 0)
	{
		number[0] = '-';
		cp_n = (unsigned short)n * -1;
	}
	else
		cp_n = (unsigned short)n;
	while (cp_n)
	{
		number[--len] = cp_n % 10 + '0';
		cp_n = cp_n / 10;
	}
	return (number);
}

static	int	nb_dg(intmax_t n)
{
	int			i;
	uintmax_t	nb;

	i = 1;
	if (n < 0)
	{
		i = 2;
		nb = (uintmax_t)n * -1;
	}
	else
		nb = (uintmax_t)n;
	while (nb > 9)
	{
		i++;
		nb = nb / 10;
	}
	return (i);
}

char		*ft_itoa_max(intmax_t n)
{
	char		*number;
	int			len;
	uintmax_t	cp_n;

	len = nb_dg(n);
	if (!(number = (char *)malloc(len + 1)))
		return (NULL);
	number[len] = '\0';
	if (!n)
		number[0] = '0';
	if (n < 0)
	{
		number[0] = '-';
		cp_n = (uintmax_t)n * -1;
	}
	else
		cp_n = (uintmax_t)n;
	while (cp_n)
	{
		number[--len] = cp_n % 10 + '0';
		cp_n = cp_n / 10;
	}
	return (number);
}

char		*ft_itoa_signchar(char n)
{
	char				*number;
	int					len;
	unsigned	char	cp_n;

	len = nb_dg(n);
	if (!(number = (char *)malloc(len + 1)))
		return (NULL);
	number[len] = '\0';
	if (!n)
		number[0] = '0';
	if (n < 0)
	{
		number[0] = '-';
		cp_n = (unsigned char)n * -1;
	}
	else
		cp_n = (unsigned char)n;
	while (cp_n)
	{
		number[--len] = cp_n % 10 + '0';
		cp_n = cp_n / 10;
	}
	return (number);
}
