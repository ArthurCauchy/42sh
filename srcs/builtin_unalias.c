/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unalias.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 17:05:12 by acauchy           #+#    #+#             */
/*   Updated: 2018/10/20 18:14:07 by ccharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "env.h"
#include "builtins.h"
#include "global.h"
#include "utils.h"
#include <stdlib.h>

int			check_alias_existance(char *key, char *value)
{
	t_alias	*head;

	head = aliases;
	while (aliases)
	{
		if (ft_strcmp(aliases->key, key) == 0)
		{
			free(aliases->value);
			aliases->value = ft_strdup(value);
			aliases = head;
			return (0);
		}
		aliases = aliases->next;
	}
	aliases = head;
	return (1);
}

static void		delete_alias(t_alias **prev, t_alias **aliases, t_alias **head,
		t_alias **tmp)
{
	if (*prev)
		(*prev)->next = (*aliases)->next;
	*tmp = (*aliases)->next;
	if (*aliases == *head)
		*head = (*aliases)->next;
	ft_multifree(3, (*aliases)->key, (*aliases)->value, *aliases);
	*aliases = *tmp;
}

static void		erase_alias(char *alias_name)
{
	t_alias *head;
	t_alias *tmp;
	t_alias	*prev;

	head = aliases;
	prev = NULL;
	while (aliases)
	{
		if (ft_strcmp(aliases->key, alias_name) == 0)
			delete_alias(&prev, &aliases, &head, &tmp);
		else
		{
			prev = aliases;
			aliases = aliases->next;
		}
	}
	aliases = head;
}

int			builtin_unalias(t_env **env, char **args)
{
	(void)env;

	if (args_size(args) > 2)
		ft_fminiprint(1, "unalias usage : %s", UNALIAS_USAGE);	
	else
	{
		erase_alias(args[1]);
		return(0);
	}
	return (-1);
}
