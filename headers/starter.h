/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   starter.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 14:11:13 by acauchy           #+#    #+#             */
/*   Updated: 2018/11/08 16:34:25 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STARTER_H
# define STARTER_H

# include "env.h"
# include "redirects.h"
# include "builtins.h"

typedef struct		s_process
{
	char		*path;
	char		**args;
	t_redirect	*redirs;
}					t_process;

/*
** process.c
*/

t_process			*new_process(t_env **cmd_env, char **args);
void				delete_process(t_process *proc);

/*
** starter.c, starter_forked.c
*/

int					start_process(t_env **cmd_env,
		t_process *proc, int forked, pid_t *pgid);
int					start_forked_builtin(t_env **cmd_env,
		t_process *proc, t_builtin *builtin, pid_t *pgid);
int					start_external_process(t_env **cmd_env,
		t_process *proc, pid_t *pgid);

#endif
