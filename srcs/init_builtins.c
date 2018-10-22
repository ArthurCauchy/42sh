/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 10:48:57 by acauchy           #+#    #+#             */
/*   Updated: 2018/10/22 16:24:01 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void		init_builtins(void)
{
	load_builtin("exit", EXIT_HELP, &builtin_exit);
	load_builtin("cd", CD_HELP, &builtin_cd);
	load_builtin("env", ENV_HELP, &builtin_env);
	load_builtin("setenv", SETENV_HELP, &builtin_setenv);
	load_builtin("unsetenv", UNSETENV_HELP, &builtin_unsetenv);
	load_builtin("echo", ECHO_HELP, &builtin_echo);
	load_builtin("which", WHICH_HELP, &builtin_which);
	load_builtin("help", HELP_HELP, &builtin_help);
	load_builtin("history", HISTORY_HELP, &builtin_history);
	load_builtin("alias", ALIAS_HELP, &builtin_alias);
	load_builtin("unalias", UNALIAS_HELP, &builtin_unalias);
}
