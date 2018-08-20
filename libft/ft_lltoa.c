/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lltoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 10:23:17 by acauchy           #+#    #+#             */
/*   Updated: 2018/01/11 14:32:58 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int	compute_nb_len(long long n)
{
	size_t	i;

	i = 0;
	while (n != 0)
	{
		n = n / 10;
		++i;
	}
	return (i);
}

static void	write_str(long long n, size_t len, char neg, char *str)
{
	size_t	i;

	i = len - 1 + neg;
	if (neg)
	{
		n *= -1;
		str[0] = '-';
	}
	while (n != 0)
	{
		str[i] = '0' + (n % 10);
		n = n / 10;
		--i;
	}
}

/*
** nb_len + neg permet d'avoir la longeur de la chaine.
** En effet nb_len = taille du nombre, neg = 0 ou 1,
** et donc aussi la taille necessaire pour un '-'.
*/

char		*ft_lltoa(long long n)
{
	char			*str;
	size_t			nb_len;
	char			neg;

	if (n == 0)
		return (ft_strdup("0"));
	nb_len = compute_nb_len(n);
	neg = 0;
	if (n < 0)
		neg = 1;
	if (!(str = malloc(nb_len + neg + 1)))
		return (NULL);
	str[nb_len + neg] = '\0';
	write_str(n, nb_len, neg, str);
	return (str);
}
