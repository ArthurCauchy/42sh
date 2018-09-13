/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saxiao <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 13:49:22 by saxiao            #+#    #+#             */
/*   Updated: 2017/12/22 02:24:37 by saxiao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stdint.h>
#include <wchar.h>
#include <stdlib.h>
#include <string.h>
#include "../../libft.h"
#include "../includes/ft_printf.h"

void			con_o(va_list args, t_data *data, char *format, int size)
{
	set_flags(args, data, format, size);
	set_cast(data, format, size);
	if (data->cast == z)
		data->ori = itoa_base(va_arg(args, size_t), 10, 8);
	else if (data->cast == none || data->cast == hh || data->cast == h)
		data->ori = itoa_base(va_arg(args, unsigned int), 10, 8);
	else if (data->cast == l)
		data->ori = itoa_base(va_arg(args, unsigned long), 10, 8);
	else if (data->cast == ll)
		data->ori = itoa_base(va_arg(args, unsigned long long), 10, 8);
	else if (data->cast == j)
		data->ori = itoa_base(va_arg(args, uintmax_t), 10, 8);
	set_print_oxu_hash(data, "0");
	free(data->ori);
}

void			con_b(va_list args, t_data *data, char *format, int size)
{
	set_flags(args, data, format, size);
	set_cast(data, format, size);
	if (data->cast == z)
		data->ori = itoa_base(va_arg(args, size_t), 10, 2);
	else if (data->cast == none || data->cast == hh || data->cast == h)
		data->ori = itoa_base(va_arg(args, unsigned int), 10, 2);
	else if (data->cast == l)
		data->ori = itoa_base(va_arg(args, unsigned long), 10, 2);
	else if (data->cast == ll)
		data->ori = itoa_base(va_arg(args, unsigned long long), 10, 2);
	else if (data->cast == j)
		data->ori = itoa_base(va_arg(args, uintmax_t), 10, 2);
	set_print_oxu_hash(data, "0");
	free(data->ori);
}

void			con_bigo(va_list args, t_data *data, char *format, int size)
{
	set_flags(args, data, format, size);
	set_cast(data, format, size);
	data->ori = itoa_base(va_arg(args, unsigned long), 10, 8);
	set_print_oxu_hash(data, "0");
	free(data->ori);
}

size_t			ft_wstrlen(wchar_t *we)
{
	size_t	i;

	i = 0;
	while (we && *we++)
		i++;
	return (i);
}

void			ft_putwstr(wchar_t *we)
{
	while (we && *we)
		ft_putwchar(*we++);
}
