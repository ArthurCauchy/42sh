/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printfcts.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/21 14:56:35 by acauchy           #+#    #+#             */
/*   Updated: 2018/01/17 14:48:44 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

static void	print_padding(int fd, int width)
{
	int	i;

	i = 0;
	while (i < width)
	{
		ft_putchar_fd(' ', fd);
		++i;
	}
}

static void	printnnbr(int fd, long long nbr, int *i, int n)
{
	if ((n == 0 || *i < n) && nbr < 0)
	{
		ft_putchar_fd('-', fd);
		nbr *= -1;
		++*i;
	}
	if ((n == 0 || *i < n) && nbr > 9)
	{
		printnnbr(fd, nbr / 10, i, n);
		printnnbr(fd, nbr % 10, i, n);
	}
	else if (n != 0 && *i >= n)
		return ;
	else
	{
		ft_putchar_fd('0' + nbr, fd);
		++*i;
	}
}

void		print_errortype(int fd, t_arg *arg, void *realarg)
{
	realarg = arg;
	arg = realarg;
	ft_putstr_fd("(type error)", fd);
}

void		print_integer(int fd, t_arg *arg, void *realarg)
{
	int			nbr;
	int			len;
	int			padding;
	int			i;

	nbr = *(int*)realarg;
	len = ft_nbrlen(nbr);
	padding = arg->width - len;
	i = 0;
	if (!arg->alignleft)
		print_padding(fd, padding);
	printnnbr(fd, nbr, &i, arg->width);
	if (arg->alignleft)
		print_padding(fd, padding);
}

void		print_string(int fd, t_arg *arg, void *realarg)
{
	char	*str;
	int		len;
	int		padding;
	int		i;

	str = (char*)realarg;
	len = ft_strlen(realarg);
	padding = arg->width - len;
	i = 0;
	if (!arg->alignleft)
		print_padding(fd, padding);
	while (i < len && (arg->width == 0 || i < arg->width))
	{
		write(fd, str + i, 1);
		++i;
	}
	if (arg->alignleft)
		print_padding(fd, padding);
}
