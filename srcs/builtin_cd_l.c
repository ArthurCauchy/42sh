/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_l.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 10:06:00 by acauchy           #+#    #+#             */
/*   Updated: 2018/08/20 17:52:27 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include "env.h"
#include "builtins.h"

static char		*add_final_slash(char **path)
{
	if ((*path)[ft_strlen(*path) - 1] != '/')
		*path = ft_strjoin_free(*path, ft_strdup("/"));
	return (*path);
}

static void		simplify(t_list **comp_lst)
{
	simplify_path_dot(comp_lst);
	simplify_path_dotdot(comp_lst);
	simplify_path_slash(comp_lst);
}

static char		*base_path(char *buff, char *path, char *old_env_pwd)
{
	char	*curpath;

	ft_strncpy(buff, path, PATH_MAX);
	if (buff[0] != '/')
		curpath = ft_strjoin(add_final_slash(&old_env_pwd), buff);
	else
		curpath = ft_strdup(buff);
	free(old_env_pwd);
	return (curpath);
}

int				try_cd_l(t_env **env, char *path)
{
	char	*curpath;
	char	buff[PATH_MAX];
	char	*old_env_pwd;
	t_list	*comp_lst;

	if (!(old_env_pwd = read_from_env(env, "PWD")))
	{
		ft_putendl_fd("cd: PWD env variable not found !", 2);
		return (1);
	}
	curpath = base_path(buff, path, old_env_pwd);
	comp_lst = str_to_compo(curpath);
	free(curpath);
	simplify(&comp_lst);
	curpath = compo_to_str(comp_lst);
	if (chdir(curpath) == -1)
	{
		print_chdir_error(path);
		free(curpath);
		return (1);
	}
	set_env(env, ft_strdup("OLDPWD"), read_from_env(env, "PWD"));
	set_env(env, ft_strdup("PWD"), ft_strdup(curpath));
	free(curpath);
	return (0);
}
