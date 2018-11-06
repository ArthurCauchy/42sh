/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 10:06:00 by acauchy           #+#    #+#             */
/*   Updated: 2018/11/06 15:23:39 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include "libft.h"
#include "env.h"
#include "utils.h"
#include "builtins.h"
#include "starter.h"

static void	add_to_tmp_env(t_env **env, char *str)
{
	char		*eq_char;

	eq_char = ft_strchr(str, '=');
	set_env(env, ft_strsub(str, 0, eq_char - str), ft_strdup(eq_char + 1));
}

static int	start_proc(char **args, t_env **tmp_env)
{
	int			ret;
	pid_t		pgid;
	int			status;
	t_process	*proc;

	pgid = -1;
	status = 0;
	proc = new_process(tmp_env, copy_args(args));
	ret = start_process(tmp_env, proc, 1, &pgid);
	delete_process(proc);
	clear_env(*tmp_env);
	if (ret > 0)
	{
		waitpid(ret, &status, WUNTRACED);
		return (get_process_return(status));
	}
	else
		return (-ret);
}

int			builtin_env(t_env **env, char **args)
{
	t_env		*tmp_env;
	int			i;
	char		options[4096];

	i = builtin_parse_options(args, options, 4096);
	if (builtin_validate_options(options, "i") == -1)
	{
		ft_putendl_fd("Usage : env [-i] [NAME=VALUE] [COMMAND]", 2);
		return (1);
	}
	tmp_env = NULL;
	if (!ft_strchr(options, 'i'))
		tmp_env = copy_env(env);
	while (args[i] && ft_strchr(args[i], '='))
	{
		add_to_tmp_env(&tmp_env, args[i]);
		++i;
	}
	if (!args[i])
	{
		print_env(&tmp_env);
		clear_env(tmp_env);
		return (0);
	}
	return (start_proc(args + i, &tmp_env));
}
