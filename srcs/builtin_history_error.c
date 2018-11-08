/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_history_error.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumenthi <lumenthi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 11:38:55 by lumenthi          #+#    #+#             */
/*   Updated: 2018/11/08 11:41:34 by lumenthi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "utils.h"
#include "env.h"
#include "global.h"
#include "history.h"

int		history_usage(char c)
{
	ft_putstr_fd("history: illegal option ", 2);
	ft_putchar_fd(c, 2);
	ft_putchar_fd('\n', 2);
	ft_putendl_fd("usage: history [-c] [-d offset] [n]", 2);
	ft_putendl_fd("       history -anrw [filename]", 2);
	ft_putendl_fd("       history -ps arg [arg ...]", 2);
	return (1);
}

int		del_error(int elem)
{
	ft_putstr_fd("history: ", 2);
	ft_putnbr_fd(elem, 2);
	ft_putstr_fd(": position out of range\n", 2);
	return (1);
}

int		del_error_alpha(char elem)
{
	ft_putstr_fd("history: ", 2);
	ft_putchar_fd(elem, 2);
	ft_putstr_fd(": position out of range\n", 2);
	return (1);
}

int		requires_error(void)
{
	ft_putendl_fd("history -d: option requires an argument", 2);
	return (1);
}

int		read_error(char *file)
{
	ft_putstr_fd("history: can't read ", 2);
	ft_putendl_fd(file, 2);
	return (1);
}
