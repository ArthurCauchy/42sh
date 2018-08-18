/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unsetenv.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 10:06:00 by acauchy           #+#    #+#             */
/*   Updated: 2018/07/17 16:37:30 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	builtin_unsetenv(t_env **env, char **args)
{
	if (!args[1])
	{
		ft_putendl_fd("unsetenv: Too few arguments.", 2);
		return (1);
	}
	unset_env(env, args[1]);
	return (0);
}
