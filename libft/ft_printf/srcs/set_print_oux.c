/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_print_oux.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saxiao <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/21 23:16:27 by saxiao            #+#    #+#             */
/*   Updated: 2017/12/22 02:47:56 by saxiao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"
#include "../includes/ft_printf.h"

static	void	for_setoux(t_data *data, char *pre_fix)
{
	if ((int)ft_strlen(data->ori) >= data->precison)
		data->len = max_3(data->width, ft_strlen(data->ori) + \
				ft_strlen(pre_fix), data->precison);
	else if (!(pre_fix[0] == '0' && !(*(pre_fix + 1))))
		data->len = max_3(data->width, ft_strlen(data->ori), \
				data->precison + ft_strlen(pre_fix));
	else
	{
		data->len = max_3(data->width, ft_strlen(data->ori), data->precison);
		data->blank = data->len - data->precison;
	}
	if (!(pre_fix[0] == '0' && !*(pre_fix + 1) &&\
				data->precison > (int)ft_strlen(data->ori)))
		data->blank = data->len - data->precison - ft_strlen(pre_fix);
}

static	void	set_oxu(t_data *data, char *pre_fix)
{
	if (data->precison == -1)
		data->no_pre = 1;
	if (!(data->ori[0] == '0' && !data->precison) && \
			data->precison < (int)ft_strlen(data->ori))
		data->precison = ft_strlen(data->ori);
	if (data->ori[0] != '0' && ft_strchr(data->flags, '#'))
		for_setoux(data, pre_fix);
	else
	{
		if (!(!data->width && data->precison <= 0 && data->ori[0] == '0'))
		{
			data->len = max_3(data->width, \
					ft_strlen(data->ori), data->precison);
			data->blank = data->len - data->precison;
		}
	}
}

static	void	for_print_oux(t_data *data, char *pre_fix)
{
	if (ft_strchr(data->flags, '#') && (!(pre_fix[0] == '0' && \
		!*(pre_fix + 1) && data->precison > (int)ft_strlen(data->ori))))
		ft_putstr(pre_fix);
	ft_putnchar('0', data->precison - ft_strlen(data->ori));
	ft_putstr(data->ori);
	ft_putnchar(' ', data->blank);
}

void			set_print_oxu_hash(t_data *data, char *pre_fix)
{
	set_oxu(data, pre_fix);
	if (!(!data->len && data->ori[0] == '0'))
	{
		if (data->ori[0] == '0')
			put_zero_oux(data);
		else
		{
			if (!ft_strchr(data->flags, '-'))
				go_right_oux(data, pre_fix);
			else
				for_print_oux(data, pre_fix);
		}
	}
	else
	{
		if (!data->precison && ft_strchr(data->flags, '#') && \
				pre_fix[0] == '0' && ft_strlen(pre_fix) == 1)
		{
			ft_putchar('0');
			data->len = 1;
		}
	}
}
