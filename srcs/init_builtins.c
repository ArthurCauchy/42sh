/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 10:48:57 by acauchy           #+#    #+#             */
/*   Updated: 2018/08/22 09:06:45 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	init_builtins(void)
{
	load_builtin("exit", &builtin_exit);
	load_builtin("cd", &builtin_cd);
	load_builtin("env", &builtin_env);
	load_builtin("setenv", &builtin_setenv);
	load_builtin("unsetenv", &builtin_unsetenv);
	load_builtin("echo", &builtin_echo);
	load_builtin("which", &builtin_which);
}
