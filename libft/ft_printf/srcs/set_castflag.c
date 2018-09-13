/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_castflag.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saxiao <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/21 22:12:26 by saxiao            #+#    #+#             */
/*   Updated: 2018/01/22 13:07:23 by saxiao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"
#include "../includes/ft_printf.h"

static	void	init(t_data *data)
{
	data->ori = NULL;
	ft_bzero(data->flags, 10);
	data->width = 0;
	data->precison = -1;
	data->len = 0;
	data->no_pre = 0;
	data->blank = 0;
	data->cast = none;
}

void			set_cast(t_data *data, char *format, int size)
{
	if (ft_strnchr(format, 'h', size))
	{
		if (ft_strnchr_double(format, 'h', size))
			data->cast = hh;
		else
			data->cast = h;
	}
	else if (ft_strnchr(format, 'l', size))
	{
		if (ft_strnchr_double(format, 'l', size))
			data->cast = ll;
		else
			data->cast = l;
	}
	else if (ft_strnchr(format, 'j', size))
		data->cast = j;
	else if (ft_strnchr(format, 'z', size))
		data->cast = z;
	else
		data->cast = none;
}

static	void	set_zero_flag(t_data *data, int *i, int *j, char *format)
{
	if (format[*i] == '.')
	{
		data->precison = ft_atoi(format + 1 + *i);
		*i = *i + nb_digit(format + *i + 1) + 1;
	}
	else
	{
		if (ft_strchr("#-+ ", format[*i]))
		{
			if (!(ft_strchr(data->flags, format[*i])))
			{
				data->flags[*j] = format[*i];
				*j = *j + 1;
			}
		}
	}
	*i = *i + 1;
}

void			flags_star(va_list args, t_data *data, char *format, int *i)
{
	if (format[*i] == '*')
	{
		data->width = va_arg(args, int);
		*i = *i + 1;
		if (data->width < 0)
			data->width = data->width * (-1);
	}
	else
	{
		data->precison = va_arg(args, int);
		*i = *i + 2;
		if (data->precison < 0)
			data->precison = -1;
	}
}

void			set_flags(va_list args, t_data *data, char *f, int size)
{
	int		i;
	int		j;

	i = 1;
	j = 0;
	init(data);
	while (i < size && j < 10)
	{
		if (f[i] == '0')
		{
			if (!(ft_strchr(data->flags, '0')))
				data->flags[j++] = '0';
			i++;
		}
		else if (!ft_strnchr(f, '.', i) && ('0' < f[i] && f[i] <= '9'))
		{
			data->width = ft_atoi(f + i);
			i = i + nb_digit(f + i);
		}
		else if (f[i] == '*' || (f[i] == '.' && f[i + 1] == '*'))
			flags_star(args, data, f, &i);
		else
			set_zero_flag(data, &i, &j, f);
	}
}
