/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 10:48:57 by acauchy           #+#    #+#             */
/*   Updated: 2018/10/15 13:09:01 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "env.h"

static void	update_shlvl(t_env **env)
{
	char	*shlvl;
	int		value;

	if ((shlvl = read_from_env(env, "SHLVL")))
	{
		if (ft_str_is_numeric(shlvl))
		{
			value = ft_atoi(shlvl);
			if (value > 0)
			{
				set_env(env, ft_strdup("SHLVL"), ft_itoa(value + 1));
				free(shlvl);
				return ;
			}
		}
	}
	set_env(env, ft_strdup("SHLVL"), ft_strdup("1"));
	free(shlvl);
}

void		init_env(t_env **env, char **envp)
{
	size_t	i;
	size_t	j;

	(void)env;
	i = 0;
	while (envp[i])
	{
		j = 0;
		while (envp[i][j])
		{
			if (envp[i][j++] == '=')
			{
				set_env(env, ft_strsub(envp[i], 0, j - 1),
						ft_strdup(&envp[i][j]));
				break ;
			}
		}
		++i;
	}
	update_shlvl(env);
}
