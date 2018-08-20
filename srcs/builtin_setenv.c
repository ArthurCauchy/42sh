/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_setenv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 10:06:00 by acauchy           #+#    #+#             */
/*   Updated: 2018/08/20 18:04:14 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "env.h"

static int	is_key_alphanum(char *key)
{
	while (*key)
	{
		if (!(ft_isalnum(*key) || *key == '_'))
			return (0);
		++key;
	}
	return (1);
}

int			builtin_setenv(t_env **env, char **args)
{
	if (!args[1])
		print_env(env);
	else
	{
		if (!is_key_alphanum(args[1]))
		{
			ft_putendl_fd("setenv: Variable name must "
					"contain alphanumeric charaters.", 2);
			return (1);
		}
		if (ft_isdigit(*args[1]))
		{
			ft_putendl_fd("setenv: Variable name must begin with a letter.", 2);
			return (1);
		}
		if (!args[2])
			set_env(env, ft_strdup(args[1]), ft_strdup(""));
		else
			set_env(env, ft_strdup(args[1]), ft_strdup(args[2]));
	}
	return (0);
}
