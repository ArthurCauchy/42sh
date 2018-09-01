/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_history.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 10:06:00 by acauchy           #+#    #+#             */
/*   Updated: 2018/08/20 18:03:52 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "env.h"
#include "builtins.h"

int			builtin_history(t_env **env, char **args)
{
	int			i;
	char		options[4096];

	(void)env;
	(void)i;
	i = builtin_parse_options(args, options, 4096);
	if (builtin_validate_options(options, "acdrnpsw") == -1) // probably need to check for incompatible options too
	{
		ft_putendl_fd("Usage : history AND SOME OPTIONS", 2); //TODO
		return (1);
	}
	ft_putstr("Options found :");
	ft_putendl(options);
	return (0);
}
