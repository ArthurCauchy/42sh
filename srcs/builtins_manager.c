/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_manager.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 14:24:18 by acauchy           #+#    #+#             */
/*   Updated: 2018/08/20 17:38:46 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "utils.h"
#include "builtins.h"

#define BUILTIN_MAX 42 //TODO a bouger dans un header ? (sauf si on s'en sert pas ailleurs)

static t_builtin	**get_builtins(void)
{
	static t_builtin	*builtins[BUILTIN_MAX] = {NULL};

	return (builtins);
}

/*
** Clear the loaded builtins.
** Has to be performed before exiting to avoid memory leaks.
*/

void				clear_builtins(void)
{
	t_builtin	**builtins;
	int			i;

	builtins = get_builtins();
	i = 0;
	while (i < BUILTIN_MAX && builtins[i] != NULL)
	{
		free(builtins[i]);
		++i;
	}
}

/*
** Loads a new builtin command.
*/

void				load_builtin(char *name, int (*func)(t_env**, char**))
{
	t_builtin	*new;
	t_builtin	**builtins;
	int			i;

	if (!(new = (t_builtin*)ft_memalloc(sizeof(t_builtin))))
		exit_error("load_builtin malloc() error");
	new->name = name;
	new->func = func;
	builtins = get_builtins();
	i = 0;
	while (i < BUILTIN_MAX && builtins[i] != NULL)
		++i;
	builtins[i] = new;
}

t_builtin_fct		search_builtin(char *name)
{
	t_builtin	**builtins;
	int			i;

	builtins = get_builtins();
	i = 0;
	while (i < BUILTIN_MAX && builtins[i] != NULL)
	{
		if (ft_strcmp(name, builtins[i]->name) == 0)
		{
			return (builtins[i]->func);
		}
		++i;
	}
	return (NULL);
}
