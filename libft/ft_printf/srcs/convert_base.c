/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_base.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saxiao <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/18 23:04:19 by saxiao            #+#    #+#             */
/*   Updated: 2017/12/22 02:46:28 by saxiao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdint.h>
#include "../includes/ft_printf.h"
#include "../../libft.h"

uintmax_t			nb_dg_inbase(uintmax_t n, unsigned int base_to)
{
	uintmax_t i;

	i = 1;
	while (n > base_to - 1)
	{
		i++;
		n = n / base_to;
	}
	return (i);
}

static	intmax_t	base_length(char *base)
{
	intmax_t		i;

	i = 0;
	while (base[i])
		i++;
	return (i);
}

static	int			position_in_base(char *base, char search)
{
	int		i;

	i = 0;
	while (search != *base)
	{
		i++;
		base++;
	}
	return (i);
}

static	char		*reverse_delect_first_zeros(char *tab, char *base_to)
{
	char	temp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (tab[j])
		j++;
	while (i < j - 1)
	{
		temp = tab[i];
		tab[i] = tab[j - 1];
		tab[j - 1] = temp;
		i++;
		j--;
	}
	while (!position_in_base(base_to, *tab))
		tab++;
	return (tab);
}

char				*ft_convert_base(char *nbr, char *base_from, char *base_to)
{
	uintmax_t		in_ten_b;
	char			*result;
	intmax_t		number_base;
	intmax_t		i;

	i = 0;
	in_ten_b = 0;
	number_base = base_length(base_from);
	while (*nbr)
		in_ten_b = in_ten_b * number_base + position_in_base(base_from, *nbr++);
	result = malloc(sizeof(*result) * (nb_dg_inbase(in_ten_b, 10) + 1));
	if (!in_ten_b)
	{
		result[0] = base_to[0];
		result[1] = '\0';
		return (result);
	}
	while (in_ten_b > 0)
	{
		result[i++] = base_to[in_ten_b % base_length(base_to)];
		in_ten_b = in_ten_b / base_length(base_to);
	}
	result[i] = '\0';
	result = reverse_delect_first_zeros(result, base_to);
	return (result);
}
