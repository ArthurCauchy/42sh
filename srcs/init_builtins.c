/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 10:48:57 by acauchy           #+#    #+#             */
/*   Updated: 2018/08/25 19:02:25 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void		init_builtins(void)
{
	load_builtin("exit", "exit [return status]\nExit the current shell.", &builtin_exit);
	load_builtin("cd", NULL, &builtin_cd);
	load_builtin("env", NULL, &builtin_env);
	load_builtin("setenv", NULL, &builtin_setenv);
	load_builtin("unsetenv", NULL, &builtin_unsetenv);
	load_builtin("echo", NULL, &builtin_echo);
	load_builtin("which", NULL, &builtin_which);
	load_builtin("help", NULL, &builtin_help);
}
