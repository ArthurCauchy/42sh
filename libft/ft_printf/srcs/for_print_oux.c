/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_print_oux.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saxiao <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/21 23:23:03 by saxiao            #+#    #+#             */
/*   Updated: 2017/12/22 02:49:49 by saxiao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"
#include "../includes/ft_printf.h"

static	void	for_right_oux(t_data *data, char *pre_fix)
{
	ft_putnchar(' ', data->blank);
	if (ft_strchr(data->flags, '#'))
	{
		if (!(pre_fix[0] == '0' && !*(pre_fix + 1) && \
					data->precison > (int)ft_strlen(data->ori)))
			ft_putstr(pre_fix);
		ft_putnchar('0', data->precison - ft_strlen(data->ori));
	}
	else
		ft_putnchar('0', data->precison - ft_strlen(data->ori));
	ft_putstr(data->ori);
}

void			go_right_oux(t_data *data, char *pre_fix)
{
	if (ft_strchr(data->flags, '0') && data->no_pre)
	{
		if (ft_strchr(data->flags, '#'))
		{
			if (!(pre_fix[0] == '0' && !*(pre_fix + 1) && \
						data->precison > (int)ft_strlen(data->ori)))
				ft_putstr(pre_fix);
			ft_putnchar('0', data->len - ft_strlen(pre_fix) - \
					ft_strlen(data->ori));
		}
		else
			ft_putnchar('0', data->len - ft_strlen(data->ori));
		ft_putstr(data->ori);
	}
	else
		for_right_oux(data, pre_fix);
}

static	void	put_nopre(t_data *data)
{
	if (!ft_strchr(data->flags, '-'))
	{
		ft_putnchar(' ', data->len - data->precison);
		ft_putnchar('0', data->precison);
	}
	else
	{
		ft_putnchar('0', data->precison);
		ft_putnchar(' ', data->len - data->precison);
	}
}

void			put_zero_oux(t_data *data)
{
	if (data->no_pre)
	{
		if (ft_strchr(data->flags, '0'))
			ft_putnchar('0', data->len);
		else
		{
			if (!ft_strchr(data->flags, '-'))
			{
				ft_putnchar(' ', data->len - 1);
				ft_putchar('0');
			}
			else
			{
				ft_putchar('0');
				ft_putnchar(' ', data->len - 1);
			}
		}
	}
	else
		put_nopre(data);
}
