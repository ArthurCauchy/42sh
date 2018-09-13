/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_dirname.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saxiao <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 12:44:42 by saxiao            #+#    #+#             */
/*   Updated: 2018/09/13 16:35:24 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "line_edit.h"

void	bg_yellow(void)
{
	ft_printf(BGYELLOW);
}

void	color_reset(void)
{
	ft_printf(RESET);
}
