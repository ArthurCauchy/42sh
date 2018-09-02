/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 10:48:57 by acauchy           #+#    #+#             */
/*   Updated: 2018/08/22 09:05:49 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init.h"

void		init(t_env **env, char **envp)
{
	init_builtins();
	init_env(env, envp);
	init_history();
}
