/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 12:23:26 by acauchy           #+#    #+#             */
/*   Updated: 2018/08/20 18:22:41 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "utils.h"
#include "env.h"

static char	*try_access_indir(char *dir, char *cmd)
{
	char	*tmp;

	tmp = ft_strjoin(dir, "/");
	tmp = ft_strjoin_free(tmp, ft_strdup(cmd));
	if (is_there_a_file(tmp))
		return (tmp);
	free(tmp);
	return (NULL);
}

static void	free_splited_path(char **array)
{
	char **cur;

	cur = array;
	while (*cur)
	{
		free(*cur);
		++cur;
	}
	free(array);
}

char		*find_cmd_path(t_env **env, t_env **cmd_env, char *cmd)
{
	char	*path;
	char	**split_path;
	char	**cur;
	char	*ret;

	if (!(path = read_from_env(cmd_env, "PATH"))
			&& !(path = read_from_env(env, "PATH")))
		return (NULL);
	ret = NULL;
	split_path = ft_strsplit(path, ':');
	cur = split_path;
	while (*cur)
	{
		if ((ret = try_access_indir(*cur, cmd)))
			break ;
		++cur;
	}
	free_splited_path(split_path);
	free(path);
	return (ret);
}
