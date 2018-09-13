/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saxiao <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 13:49:22 by saxiao            #+#    #+#             */
/*   Updated: 2017/12/22 03:09:38 by saxiao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stdlib.h>
#include <stdint.h>
#include "../../libft.h"
#include "../includes/ft_printf.h"

static	void	set_print_s(t_data *data)
{
	int		nbr_l;

	nbr_l = 0;
	if (data->precison == -1)
		data->precison = ft_strlen(data->ori);
	if (data->precison > (int)ft_strlen(data->ori))
		nbr_l = ft_strlen(data->ori);
	else
		nbr_l = data->precison;
	data->len = max_2(data->width, nbr_l);
	if (ft_strchr(data->flags, '-'))
	{
		ft_putnstr(data->ori, nbr_l);
		ft_putnchar(' ', data->len - nbr_l);
	}
	else
	{
		ft_putnchar(' ', data->len - nbr_l);
		ft_putnstr(data->ori, nbr_l);
	}
}

static	void	set_print_bigs(t_data *data, wchar_t *we)
{
	int		nbr_l;

	nbr_l = 0;
	if (data->precison == -1)
		data->precison = ft_wstrlen(we);
	if (data->precison > (int)ft_wstrlen(we))
		nbr_l = ft_wstrlen(we);
	else
		nbr_l = data->precison;
	data->len = max_2(data->width, nbr_l);
	if (ft_strchr(data->flags, '-'))
	{
		ft_putnwstr(we, nbr_l);
		ft_putnchar(' ', data->len - nbr_l);
	}
	else
	{
		ft_putnchar(' ', data->len - nbr_l);
		ft_putnwstr(we, nbr_l);
	}
}

void			con_s(va_list args, t_data *data, char *format, int size)
{
	wchar_t		*we;

	set_flags(args, data, format, size);
	set_cast(data, format, size);
	if (data->cast == l)
	{
		we = va_arg(args, wchar_t *);
		set_print_bigs(data, we);
	}
	else
	{
		data->ori = va_arg(args, char *);
		if (!data->ori)
		{
			data->ori = ft_strdup("(null)");
			set_print_s(data);
			free(data->ori);
		}
		else
			set_print_s(data);
	}
}

void			con_bigs(va_list args, t_data *data, char *format, int size)
{
	wchar_t		*we;

	we = va_arg(args, wchar_t *);
	set_flags(args, data, format, size);
	set_cast(data, format, size);
	set_print_bigs(data, we);
}
