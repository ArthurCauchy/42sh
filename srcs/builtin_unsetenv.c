/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unsetenv.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 10:06:00 by acauchy           #+#    #+#             */
/*   Updated: 2018/08/20 18:04:40 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "env.h"

int	builtin_unsetenv(t_env **env, char **args)
{
	int	i;

	if (!args[1])
	{
		ft_putendl_fd("unsetenv: Too few arguments.", 2);
		return (1);
	}
	i = 1;
	while (args[i])
	{
		unset_env(env, args[i]);
		++i;
	}
	return (0);
}
