/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_help.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 10:06:00 by acauchy           #+#    #+#             */
/*   Updated: 2018/08/25 19:01:24 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "env.h"
#include "builtins.h"

int			builtin_help(t_env **env, char **args)
{
	t_builtin	*builtin;

	(void)env;
	if (!args[1])
	{
		ft_putendl("Usage: history [builtin]");
		//ft_putendl("Available builtins :");
		//TODO print builtin list here. Need to create a function to get the full builtin list.
	}
	else if (args[2])
		ft_putendl_fd("Too many arguments.", 2);
	else
	{
		if ((builtin = search_builtin(args[1])))
		{
			if (builtin->brief)
			{
				ft_putendl(builtin->brief);
				return (0);
			}
			else
				ft_putendl_fd("No help for this builtin.", 2);
		}
		else
			ft_putendl_fd("Builtin not found.", 2);
	}
	return (1);
}
