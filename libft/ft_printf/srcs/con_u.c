/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saxiao <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 13:49:22 by saxiao            #+#    #+#             */
/*   Updated: 2017/12/22 02:33:36 by saxiao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stdint.h>
#include <stdlib.h>
#include "../../libft.h"
#include "../includes/ft_printf.h"

static	void	cast_nu_u(va_list args, t_data *data, char *format, int size)
{
	set_cast(data, format, size);
	if (data->cast == z)
		data->ori = ft_itoa_unmax(va_arg(args, size_t));
	else if (data->cast == none || data->cast == hh || data->cast == h)
		data->ori = ft_itoa_unmax(va_arg(args, unsigned int));
	else if (data->cast == l)
		data->ori = ft_itoa_unmax(va_arg(args, unsigned long));
	else if (data->cast == ll)
		data->ori = ft_itoa_unmax(va_arg(args, unsigned long long));
	else if (data->cast == j)
		data->ori = ft_itoa_unmax(va_arg(args, uintmax_t));
}

void			con_u(va_list args, t_data *data, char *format, int size)
{
	set_flags(args, data, format, size);
	cast_nu_u(args, data, format, size);
	set_print_oxu_hash(data, "");
	free(data->ori);
}

void			con_bigu(va_list args, t_data *data, char *format, int size)
{
	set_flags(args, data, format, size);
	set_cast(data, format, size);
	data->ori = ft_itoa_max(va_arg(args, unsigned long));
	set_print_oxu_hash(data, "");
	free(data->ori);
}
