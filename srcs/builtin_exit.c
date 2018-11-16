/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 10:06:00 by acauchy           #+#    #+#             */
/*   Updated: 2018/11/16 18:26:17 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "env.h"
#include "history.h"
#include "builtins.h"
#include "global.h"

int	builtin_exit(t_env **env, char **args)
{
	int	exit_status;

	exit_status = 0;
	if (args[1])
	{
		if (ft_str_is_numeric(args[1]))
		{
			exit_status = ft_atoi(args[1]);
			if (args[2])
			{
				ft_putendl_fd("exit: Too many arguments.", 2);
				return (1);
			}
		}
		else
		{
			exit_status = 255;
			ft_putendl_fd("exit: Numeric argument required.", 2);
		}
	}
	history_exit();
	clear_builtins();
	clear_env(*env);
	exit(exit_status);
	return (0);
}
