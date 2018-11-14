/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_auto_complet.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saxiao <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/17 15:05:59 by saxiao            #+#    #+#             */
/*   Updated: 2018/11/13 12:49:54 by saxiao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <curses.h>
#include <term.h>
#include <dirent.h>
#include "line_edit.h"

static t_autolist	*addlist_in_path(t_line *line, char **path, t_autolist *l)
{
	DIR				*dirp;
	struct dirent	*dir;

	while (path && *path)
	{
		if ((dirp = opendir(*path)))
		{
			while ((dir = readdir(dirp)))
			{
				if (!ft_strncmp((char *)line->auto_compare, dir->d_name, \
							ft_strlen((char *)line->auto_compare)) && \
						!(!ft_strlen((char *)line->auto_compare) && \
							dir->d_name[0] == '.'))
					l = add_a_list(l, (char *)dir->d_name, dir->d_type);
			}
			closedir(dirp);
		}
		path++;
	}
	if (!auto_current(line))
		l = addlist_buildin_alias(line, l);
	return (l);
}

void				path_last_slash(char *start, char *dic, int index)
{
	int		i;

	i = ft_strlen(start) - 1;
	while (i >= 0 && start[i] != '/')
		i--;
	ft_bzero(dic, index);
	ft_strncpy(dic, start, i + 1);
}

static t_autolist	*addlist_no_path(t_line *line, t_autolist *list)
{
	DIR				*dirp;
	struct dirent	*dir;
	char			dic[INPUT_MAX_LEN];

	path_last_slash((char *)line->auto_compare, dic, INPUT_MAX_LEN);
	if ((dirp = opendir(dic)))
	{
		while ((dir = readdir(dirp)))
		{
			if (!ft_strncmp((char *)line->auto_compare + ft_strlen(dic), \
						dir->d_name, ft_strlen((char *)line->auto_compare + \
							ft_strlen(dic))))
				list = add_a_list(list, dir->d_name, dir->d_type);
		}
		closedir(dirp);
	}
	return (list);
}

t_autolist			*get_autolist(t_line *line, t_env **env)
{
	t_autolist	*list;
	char		**all;

	list = NULL;
	all = NULL;
	if (auto_current(line))
		all = ft_split("./", " ");
	else
		all = path(env);
	if (!ft_strchr((char *)line->auto_compare, '/'))
	{
		if (ft_strlen((char *)line->auto_compare) || (all && \
					!ft_strcmp(all[0], "./")))
			list = addlist_in_path(line, all, list);
	}
	else
		list = addlist_no_path(line, list);
	ft_freestrstr(all);
	return (list);
}
