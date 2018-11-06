/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_manager.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 14:24:18 by acauchy           #+#    #+#             */
/*   Updated: 2018/11/06 15:04:24 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "utils.h"
#include "builtins.h"

t_builtin	**get_builtins(void)
{
	static t_builtin	*builtins[BUILTINS_MAX] = {NULL};

	return (builtins);
}

/*
** Clear the loaded builtins.
*/

void		clear_builtins(void)
{
	t_builtin	**builtins;
	int			i;

	builtins = get_builtins();
	i = 0;
	while (i < BUILTINS_MAX && builtins[i] != NULL)
	{
		free(builtins[i]);
		builtins[i] = NULL;
		++i;
	}
}

/*
** Loads a new builtin command.
** Input: the name of the builtin and the function that IS the builtin.
** This registers the builtin which can then be found using "search_builtin()"
*/

void		load_builtin(char *name, char *brief, int (*func)(t_env**, char**))
{
	t_builtin	*new;
	t_builtin	**builtins;
	int			i;

	if (!(new = (t_builtin*)ft_memalloc(sizeof(t_builtin))))
		exit_error("load_builtin malloc() error");
	new->name = name;
	new->brief = brief;
	new->func = func;
	builtins = get_builtins();
	i = 0;
	while (i < BUILTINS_MAX && builtins[i] != NULL)
		++i;
	builtins[i] = new;
}

/*
** Search a builtin by his name in the builtin register.
** Returns a pointer to the corresponding builtin struct, or NULL if not found.
*/

t_builtin	*search_builtin(char *name)
{
	t_builtin	**builtins;
	int			i;

	builtins = get_builtins();
	i = 0;
	while (i < BUILTINS_MAX && builtins[i] != NULL)
	{
		if (ft_strcmp(name, builtins[i]->name) == 0)
			return (builtins[i]);
		++i;
	}
	return (NULL);
}
