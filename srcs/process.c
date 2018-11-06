/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 12:43:30 by acauchy           #+#    #+#             */
/*   Updated: 2018/11/06 11:57:39 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "utils.h"
#include "path.h"
#include "starter.h"
#include "global.h"

static char	*get_proc_path(t_env **cmd_env, char *name)
{
	char	*after_path;

	if (ft_strchr(name, '/') && is_there_a_file(name))
		return (ft_strdup(name));
	else if (!ft_strchr(name, '/')
			&& (after_path = find_cmd_path(&g_env, cmd_env, name)))
		return (after_path);
	else
		return (NULL);
}

t_process	*new_process(t_env **cmd_env, char **args)
{
	t_process	*new;

	new = (t_process*)malloc(sizeof(t_process));
	new->path = get_proc_path(cmd_env, args[0]);
	new->args = args;
	new->redirs = NULL;
	return (new);
}

void		delete_process(t_process *proc)
{
	free(proc->path);
	delete_args(proc->args);
	free(proc);
}
