/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_add_a_list_nbuildin.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saxiao <saxiao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/17 16:45:17 by saxiao            #+#    #+#             */
/*   Updated: 2018/11/09 15:17:17 by lumenthi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <dirent.h>
#include "line_edit.h"
#include "global.h"

t_autolist			*add_one_list(t_autolist *list, t_autolist *add)
{
	t_autolist	*cp;

	cp = list;
	if (!cp)
	{
		add->pre = NULL;
		add->ct = 0;
		return (add);
	}
	while (cp->next)
		cp = cp->next;
	add->pre = cp;
	add->ct = cp->ct + 1;
	cp->next = add;
	return (list);
}

/*
** Params :
** - list : autocompletion list
** - name : the name of this element of the list
** - type : 0 = regular file, 1 = directory
*/

t_autolist			*add_a_list(t_autolist *l, char *name, unsigned char type)
{
	t_autolist		*add;

	add = malloc(sizeof(t_autolist));
	add->next = NULL;
	ft_bzero(add->name, INPUT_MAX_LEN);
	ft_strncpy(add->name, name, INPUT_MAX_LEN - 1);
	add->len = ft_strlen(add->name);
	if (type == DT_DIR)
		add->is_dic = 1;
	else
		add->is_dic = 0;
	l = add_one_list(l, add);
	return (l);
}

static int			buildin_exit(t_autolist *list, char *buildin)
{
	t_autolist		*cp;

	cp = list;
	while (cp)
	{
		if (!ft_strcmp(cp->name, buildin))
			return (1);
		cp = cp->next;
	}
	return (0);
}

static t_autolist	*addlist_alias(t_line *line, t_autolist *list)
{
	t_alias		*cp;

	cp = g_aliases;
	while (cp)
	{
		if (!ft_strncmp((char *)line->auto_compare, cp->key, \
					ft_strlen((char *)line->auto_compare)) \
				&& !buildin_exit(list, cp->key))
			list = add_a_list(list, cp->key, 0);
		cp = cp->next;
	}
	return (list);
}

t_autolist			*addlist_buildin_alias(t_line *line, t_autolist *list)
{
	char			*buildin[7];
	int				i;

	buildin[0] = "cd";
	buildin[1] = "env";
	buildin[2] = "setenv";
	buildin[3] = "unsetenv";
	buildin[4] = "echo";
	buildin[5] = "exit";
	buildin[6] = NULL;
	i = -1;
	while (++i < 6)
	{
		if (!ft_strncmp((char *)line->auto_compare, buildin[i], \
					ft_strlen((char *)line->auto_compare)) \
				&& !buildin_exit(list, buildin[i]))
			list = add_a_list(list, buildin[i], 0);
	}
	list = addlist_alias(line, list);
	return (list);
}
