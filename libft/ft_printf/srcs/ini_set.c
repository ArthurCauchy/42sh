/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saxiao <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 14:11:07 by saxiao            #+#    #+#             */
/*   Updated: 2017/12/22 06:24:23 by saxiao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"
#include "../includes/ft_printf.h"

int				is_f(char c)
{
	return (c == 's' || c == 'S' || c == 'p' || c == 'd' || c == 'D' || \
	c == 'i' || c == 'o' || c == 'O' || c == 'u' || c == 'U' || c == 'x' \
	|| c == 'X' || c == 'c' || c == 'C' || c == 'b');
}

static	void	for_iniset(t_fu *set)
{
	set[7].c = 'c';
	set[7].func = con_c;
	set[8].c = 'C';
	set[8].func = con_bigc;
	set[9].c = 'u';
	set[9].func = con_u;
	set[10].c = 'U';
	set[10].func = con_bigu;
	set[11].c = '%';
	set[11].func = con_per;
	set[11].c = '%';
	set[11].func = con_per;
	set[12].c = 'p';
	set[12].func = con_p;
	set[13].c = 'x';
	set[13].func = con_x;
	set[14].c = 'X';
	set[14].func = con_bigx;
	set[15].c = 'b';
	set[15].func = con_b;
}

void			ini_set(t_fu *set, t_mark *m)
{
	set[0].c = 's';
	set[0].func = con_s;
	set[1].c = 'S';
	set[1].func = con_bigs;
	set[2].c = 'o';
	set[2].func = con_o;
	set[3].c = 'O';
	set[3].func = con_bigo;
	set[4].c = 'd';
	set[4].func = con_d;
	set[5].c = 'D';
	set[5].func = con_bigd;
	set[6].c = 'i';
	set[6].func = con_d;
	for_iniset(set);
	m->nbr = 0;
}

void			add_hash_p(t_data *data)
{
	int		i;

	i = 0;
	while ((data->flags)[i])
		i++;
	(data->flags)[i] = '#';
}
