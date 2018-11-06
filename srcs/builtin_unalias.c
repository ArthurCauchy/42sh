/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unalias.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 17:05:12 by acauchy           #+#    #+#             */
/*   Updated: 2018/11/06 16:06:41 by ccharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "env.h"
#include "builtins.h"
#include "global.h"
#include "utils.h"
#include <stdlib.h>

void			delete_all_aliases(t_alias *alias)
{
	t_alias		*tmp;

	if (alias)
	{
		ft_strdel(&alias->key);
		ft_strdel(&alias->value);
		tmp = alias->next;
		free(alias);
		delete_all_aliases(tmp);
	}
	g_aliases = NULL;
}

int				check_alias_existance(char *key, char *value)
{
	t_alias	*head;

	head = g_aliases;
	if (check_alias_forbid_char(value) == -1)
		return (-1);
	while (g_aliases)
	{
		if (ft_strcmp(g_aliases->key, key) == 0)
		{
			free(g_aliases->value);
			if (value)
				g_aliases->value = ft_strdup(value);
			else
				g_aliases->value = ft_strdup("");
			g_aliases = head;
			return (0);
		}
		g_aliases = g_aliases->next;
	}
	g_aliases = head;
	return (1);
}

static void		delete_alias(t_alias **prev, t_alias **g_aliases,
		t_alias **head, t_alias **tmp)
{
	if (*prev)
		(*prev)->next = (*g_aliases)->next;
	*tmp = (*g_aliases)->next;
	if (*g_aliases == *head)
		*head = (*g_aliases)->next;
	ft_multifree(3, (*g_aliases)->key, (*g_aliases)->value, *g_aliases);
	*g_aliases = *tmp;
}

static void		erase_alias(char *alias_name)
{
	t_alias *head;
	t_alias *tmp;
	t_alias	*prev;

	head = g_aliases;
	prev = NULL;
	while (g_aliases)
	{
		if (ft_strcmp(g_aliases->key, alias_name) == 0)
			delete_alias(&prev, &g_aliases, &head, &tmp);
		else
		{
			prev = g_aliases;
			g_aliases = g_aliases->next;
		}
	}
	g_aliases = head;
}

int				builtin_unalias(t_env **env, char **args)
{
	(void)env;
	if (args_size(args) != 2)
		ft_fminiprint(1, "unalias usage : %l0s%\n", UNALIAS_USAGE);
	else if (args[1][0] == '-')
	{
		if (ft_strcmp(args[1], "-a") == 0)
		{
			delete_all_aliases(g_aliases);
			return (0);
		}
		else
		{
			ft_fminiprint(1, "unalias : illegal option %l0s%\n", args[1]);
			ft_fminiprint(1, "usage : %l0s%\n", UNALIAS_USAGE);
		}
	}
	else
	{
		erase_alias(args[1]);
		return (0);
	}
	return (-1);
}
