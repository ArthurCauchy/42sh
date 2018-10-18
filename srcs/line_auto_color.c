/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_dirname.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saxiao <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 12:44:42 by saxiao            #+#    #+#             */
/*   Updated: 2018/10/18 14:15:20 by saxiao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "line_edit.h"
#include "colors.h"

void	bg_yellow(void)
{
	ft_printf(BGYELLOW);
}

void	boldgreen(void)
{
	ft_printf(BOLDGREEN);
}

void	blue(void)
{
	ft_printf(BLUE);
}

void	color_reset(void)
{
	ft_printf(RESET);
}
