/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_help.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 10:06:00 by acauchy           #+#    #+#             */
/*   Updated: 2018/10/19 15:01:03 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "utils.h"
#include "env.h"
#include "builtins.h"

static void	print_builtins_list(void)
{
	t_builtin	**builtins;
	int			i;

	builtins = get_builtins();
	i = 0;
	while (i < BUILTINS_MAX && builtins[i] != NULL)
	{
		ft_putstr_fd("- ", 2);
		ft_putendl_fd(builtins[i]->name, 2);
		++i;
	}
}

int			builtin_help(t_env **env, char **args)
{
	t_builtin	*builtin;

	(void)env;
	if (!args[1])
	{
		ft_putendl_fd("Usage: history [builtin]", 2);
		ft_putendl_fd("\nAvailable builtins :", 2);
		print_builtins_list();
	}
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
