/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   con_d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saxiao <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/20 13:50:53 by saxiao            #+#    #+#             */
/*   Updated: 2017/12/22 02:51:57 by saxiao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stdlib.h>
#include <stdint.h>
#include "../../libft.h"
#include "../includes/ft_printf.h"

static	void	cast_nu_d(va_list args, t_data *data, char *format, int size)
{
	set_cast(data, format, size);
	if (data->cast == z)
		data->ori = ft_itoa_max(va_arg(args, size_t));
	else	if (data->cast == none)
		data->ori = ft_itoa(va_arg(args, int));
	else	if (data->cast == hh)
		data->ori = ft_itoa_signchar(va_arg(args, int));
	else	if (data->cast == h)
		data->ori = ft_itoa_short(va_arg(args, int));
	else	if (data->cast == l)
		data->ori = ft_itoa_max(va_arg(args, long int));
	else	if (data->cast == ll)
		data->ori = ft_itoa_max(va_arg(args, long long int));
	else	if (data->cast == j)
		data->ori = ft_itoa_max(va_arg(args, intmax_t));
}

static	void	zero_noze(t_data *data)
{
	if (!ft_strchr(data->flags, '+') && !ft_strchr(data->flags, ' '))
		ft_putnchar(' ', data->len);
	else
	{
		if (ft_strchr(data->flags, '+'))
			ft_putchar('+');
		else
			ft_putchar(' ');
		ft_putnchar(' ', data->len - 1);
	}
}

void			put_zero_d(t_data *data)
{
	if (ft_strchr(data->flags, '0') && data->no_pre)
	{
		if (!ft_strchr(data->flags, '+') && !ft_strchr(data->flags, ' '))
			ft_putnchar('0', data->len);
		else
		{
			if (ft_strchr(data->flags, '+'))
				ft_putchar('+');
			else
				ft_putchar(' ');
			ft_putnchar('0', data->len - 1);
		}
	}
	else
		zero_noze(data);
}

void			con_d(va_list args, t_data *data, char *format, int size)
{
	set_flags(args, data, format, size);
	cast_nu_d(args, data, format, size);
	set_print_d(data);
	free(data->ori);
}

void			con_bigd(va_list args, t_data *data, char *format, int size)
{
	set_flags(args, data, format, size);
	set_cast(data, format, size);
	data->ori = ft_itoa_max(va_arg(args, long int));
	set_print_d(data);
	free(data->ori);
}
