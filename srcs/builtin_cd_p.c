/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_p.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 10:06:00 by acauchy           #+#    #+#             */
/*   Updated: 2018/08/20 18:02:56 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include "env.h"
#include "builtins.h"

int	try_cd_p(t_env **env, char *path)
{
	char	curpath[PATH_MAX];
	char	curr_pwd[PATH_MAX];
	char	old_pwd[PATH_MAX];
	char	*success;

	ft_strncpy(curpath, path, PATH_MAX);
	success = getcwd(old_pwd, PATH_MAX);
	if (chdir(curpath) == -1)
	{
		print_chdir_error(path);
		return (1);
	}
	if (success)
		set_env(env, ft_strdup("OLDPWD"), ft_strdup(old_pwd));
	if (!getcwd(curr_pwd, PATH_MAX))
	{
		ft_putendl_fd("cd: Error with the new current directory.", 2);
		return (1);
	}
	set_env(env, ft_strdup("PWD"), ft_strdup(curr_pwd));
	return (0);
}
