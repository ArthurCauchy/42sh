/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   starter.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 14:11:13 by acauchy           #+#    #+#             */
/*   Updated: 2018/11/01 14:25:47 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STARTER_H
# define STARTER_H

# include "env.h"
# include "redirects.h"

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
** starter.c
*/

int					start_process(t_env **cmd_env, t_process *proc, int forked, pid_t *pgid);

#endif
