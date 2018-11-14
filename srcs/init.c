/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 10:48:57 by acauchy           #+#    #+#             */
/*   Updated: 2018/11/14 11:19:11 by saxiao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <unistd.h>
#include "init.h"
#include "global.h"

void		init(t_env **env, char **envp)
{
	if (!isatty(0))
		exit_error("STDIN (0) is not a tty !");
	g_shell_pid = getpid();
	setpgid(g_shell_pid, g_shell_pid);
	tcsetpgrp(0, g_shell_pid);
	init_signals();
	init_builtins();
	init_env(env, envp);
	init_termios();
	init_history(env);
}
