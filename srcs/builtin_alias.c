/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_alias.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 17:05:12 by acauchy           #+#    #+#             */
/*   Updated: 2018/10/20 18:14:17 by ccharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "builtins.h"
#include "env.h"
#include "global.h"
#include "utils.h"
#include <stdlib.h>

static void    display_aliases(void)
{
	t_alias *head;

	head = aliases;
	while (aliases)
	{
		ft_putstr(aliases->key);
		ft_putchar('=');
		ft_putendl(aliases->value);
		aliases = aliases->next;
	}
	aliases = head;
}

static void    	alias_pushback(t_alias **new_alias)
{
	t_alias *head;

	head = aliases;
	if (!(aliases))
		aliases = *new_alias;
	else
	{
		while (aliases->next)
			aliases = aliases->next;
		aliases->next = *new_alias;
		aliases = head;
	}
}

static int		malloc_alias(char **alias, t_alias **new_alias)
{
	if (!(*new_alias = (t_alias *)malloc(sizeof(t_alias))))
		return (-1);
	(*new_alias)->key = ft_strdup(alias[0]);
	(*new_alias)->value = ft_strdup(alias[1]);
	(*new_alias)->next = NULL;
	alias_pushback(new_alias);
	return (0);
}

static int		create_alias(char **alias)
{
	int			i;
	t_alias		*new_alias;

	i = -1;
	new_alias = NULL;
	if (args_size(alias) > 2)
	{
		ft_putendl("alias error : multiple '=' separator detected");
		return (-1);
	}
	while (alias[0][++i])
	{
		if (!(ft_isalnum(alias[0][i])))
		{
			ft_putendl("Alias error : non-alphanumeric chars in alias name");
			return (-1);
		}
	}
	if (check_alias_existance(alias[0], alias[1]))
		malloc_alias(alias, &new_alias);
	return (0);
}

int			builtin_alias(t_env **env, char **args)
{
	char **alias;	
	
	(void)env;
	
	if (args_size(args) > 2)
		ft_fminiprint(1, "alias usage : %s", ALIAS_USAGE);
	else if (args_size(args) == 1)
		display_aliases();
	else if (!(ft_strchr(args[1], '=')))
		ft_putendl("alias error : missing '=' between name and value");
	else
	{	
		alias = ft_strsplit(args[1], '=');
		if (!(create_alias(alias)))
		{
			delete_args(alias);
			return (-1);
		}
		delete_args(alias);
		return (0);
	}
	return (-1);
}
