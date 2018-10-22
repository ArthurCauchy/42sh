/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unalias.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 17:05:12 by acauchy           #+#    #+#             */
/*   Updated: 2018/10/22 15:40:38 by ccharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "env.h"
#include "builtins.h"
#include "global.h"
#include "utils.h"
#include <stdlib.h>

int				check_alias_existance(char *key, char *value)
{
	t_alias	*head;

	head = g_aliases;
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
		ft_fminiprint(1, "unalias usage : %l0s%", UNALIAS_USAGE);
	else
	{
		erase_alias(args[1]);
		return (0);
	}
	return (-1);
}
