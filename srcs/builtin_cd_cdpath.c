/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_cdpath.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 10:06:00 by acauchy           #+#    #+#             */
/*   Updated: 2018/09/20 14:50:20 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "utils.h"
#include "env.h"

static char	**cdpath_strsplit(char *str)
{
	char	**array;
	size_t	i;
	size_t	last;
	size_t	cur;

	i = 0;
	last = 0;
	cur = 0;
	if (!str)
		return (NULL);
	if (!(array = ft_memalloc((ft_count(str, ':') + 2) * sizeof(char*))))
		exit_error("ft_memalloc() error");
	while (str[i])
	{
		if (str[i] == ':')
		{
			array[cur++] = ft_strndup(str + last, i - last);
			last = i + 1;
		}
		++i;
	}
	array[cur++] = ft_strndup(str + last, i - last);
	return (array);
}

static int	ends_with_slash(char *str)
{
	char	prev;

	prev = -1;
	while (*str)
	{
		prev = *str;
		++str;
	}
	if (prev == '/')
		return (1);
	return (0);
}

static char	*try_pathname(char *pathname, char *dir)
{
	char	*tmp;
	char	*concat;

	if (!ends_with_slash(pathname))
	{
		tmp = ft_strjoin(pathname, "/");
		concat = ft_strjoin(tmp, dir);
		free(tmp);
	}
	else
		concat = ft_strjoin(pathname, dir);
	if (is_directory(concat))
		return (concat);
	free(concat);
	return (NULL);
}

char		*search_cdpath(t_env **env, char *path)
{
	char	*cdpath;
	char	**split_cdpath;
	char	**cur;
	char	*ret;

	if (!(cdpath = read_from_env(env, "CDPATH")))
		return (NULL);
	split_cdpath = cdpath_strsplit(cdpath);
	cur = split_cdpath;
	ret = NULL;
	while (*cur)
	{
		if (ft_strcmp(*cur, "") == 0)
		{
			if ((ret = try_pathname("./", path)))
				break ;
		}
		else if ((ret = try_pathname(*cur, path)))
			break ;
		++cur;
	}
	delete_args(split_cdpath);
	free(cdpath);
	return (ret);
}
