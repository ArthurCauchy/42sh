/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   con_d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saxiao <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/20 13:50:53 by saxiao            #+#    #+#             */
/*   Updated: 2017/12/21 23:47:13 by saxiao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"
#include "../includes/ft_printf.h"

static	void	set_d_len(t_data *data)
{
	if (data->ori[0] != '-')
	{
		data->len = max_3(data->width, ft_strlen(data->ori), data->precison);
		data->blank = data->len - data->precison;
		if (ft_strchr(data->flags, ' ') || ft_strchr(data->flags, '+'))
		{
			if (data->len == data->precison)
				data->len++;
			else
				data->blank--;
		}
	}
	else
	{
		data->len = max_2(data->width, data->precison);
		data->blank = data->len - data->precison;
		if (data->len == data->precison)
			data->len++;
		else
			data->blank--;
	}
}

static	void	set_d(t_data *data)
{
	if (data->precison == -1)
		data->no_pre = 1;
	if (!(data->ori[0] == '0' && !data->precison))
	{
		if (data->ori[0] != '-' && data->precison < (int)ft_strlen(data->ori))
			data->precison = ft_strlen(data->ori);
		else if (data->ori[0] == '-' && data->precison < \
				(int)ft_strlen(data->ori) - 1)
			data->precison = ft_strlen(data->ori) - 1;
	}
	if (!(data->ori[0] == '0' && !data->precison))
		set_d_len(data);
	else
		data->len = data->width;
}

static	void	plus_blank(t_data *data)
{
	if (data->ori[0] != '-')
	{
		if (ft_strchr(data->flags, '+'))
			ft_putchar('+');
		else if (ft_strchr(data->flags, ' '))
			ft_putchar(' ');
	}
	else
		ft_putchar('-');
}

static	void	go_right(t_data *data)
{
	if (ft_strchr(data->flags, '0') && data->no_pre)
	{
		plus_blank(data);
		ft_putnchar('0', data->blank);
		if (data->ori[0] == '-')
			ft_putstr(data->ori + 1);
		else
			ft_putstr(data->ori);
	}
	else
	{
		ft_putnchar(' ', data->blank);
		plus_blank(data);
		if (data->ori[0] == '-')
		{
			ft_putnchar('0', data->precison - ft_strlen(data->ori) + 1);
			ft_putstr(data->ori + 1);
		}
		else
		{
			ft_putnchar('0', data->precison - ft_strlen(data->ori));
			ft_putstr(data->ori);
		}
	}
}

void			set_print_d(t_data *data)
{
	set_d(data);
	if (data->len && !(data->ori[0] == '0' && !data->precison))
	{
		if (!ft_strchr(data->flags, '-'))
			go_right(data);
		else
		{
			plus_blank(data);
			if (data->ori[0] == '-')
				ft_putnchar('0', data->precison - ft_strlen(data->ori) + 1);
			else
				ft_putnchar('0', data->precison - ft_strlen(data->ori));
			if (data->ori[0] == '-')
				ft_putstr(data->ori + 1);
			else
				ft_putstr(data->ori);
			ft_putnchar(' ', data->blank);
		}
	}
	else if (data->len && data->ori[0] == '0')
		put_zero_d(data);
}
