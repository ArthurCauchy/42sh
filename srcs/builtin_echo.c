/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 10:06:00 by acauchy           #+#    #+#             */
/*   Updated: 2018/07/17 14:35:55 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int			builtin_echo(t_env **env, char **args)
{
	ssize_t	i;

	(void)env;
	i = 1;
	while (args[i])
	{
		if (i != 1)
			ft_putchar(' ');
		ft_putstr(args[i]);
		++i;
	}
	ft_putchar('\n');
	return (0);
}
