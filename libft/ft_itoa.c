/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 10:23:17 by acauchy           #+#    #+#             */
/*   Updated: 2017/11/17 11:50:38 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int	compute_nb_len(int n)
{
	long	nb;
	size_t	i;

	nb = n;
	i = 0;
	while (nb != 0)
	{
		nb = nb / 10;
		++i;
	}
	return (i);
}

static void	write_str(int n, size_t len, char neg, char *str)
{
	long	nb;
	size_t	i;

	nb = n;
	i = len - 1 + neg;
	if (neg)
	{
		nb *= -1;
		str[0] = '-';
	}
	while (nb != 0)
	{
		str[i] = '0' + (nb % 10);
		nb = nb / 10;
		--i;
	}
}

/*
** nb_len + neg permet d'avoir la longeur de la chaine.
** En effet nb_len = taille du nombre, neg = 0 ou 1,
** et donc aussi la taille necessaire pour un '-'.
*/

char		*ft_itoa(int n)
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
