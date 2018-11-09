/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 14:20:15 by acauchy           #+#    #+#             */
/*   Updated: 2018/11/09 15:02:36 by lumenthi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __INTERPRETER_H
# define __INTERPRETER_H

# include "parsing.h"
# include "starter.h"

typedef struct	s_interpret
{
	int			*child_fds;
	t_process	*proc;
	int			pl_size;
	pid_t		pgid;
	int			status;
	int			ret;
	t_redirect	*redirs;
	char		*errmsg;
}				t_interpret;

/*
** interpreter.c
*/

int				do_interpret(t_env **cmd_env, t_parse_block *parsed);

/*
** interpreter_run.c
*/

void			handle_end(int *pipefd, char **tmp_str, t_redirect **redirs);
int				close_fd(int fd);
void			handle_pipes(t_parse_block *pipeline, t_redirect **redirs);
void			interpret_loops(t_interpret *interpret, t_env **cmd_env,
				t_parse_block *pipeline);
void			interpret_wait(t_interpret *interpret);

#endif
