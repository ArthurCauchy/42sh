/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/30 12:07:09 by acauchy           #+#    #+#             */
/*   Updated: 2018/09/20 14:54:06 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** read options given to a command
** Params:
** - char **args : the command arguments
** - char *options : the buffer where to store found options
** - int options_size : the size of the buffer
** Return: the index of the first non-option parameter
**
** Note that the "options" buffer will be bzero'ed by this function.
*/

int		builtin_parse_options(char **args, char *options, int options_size)
{
	int		i;
	int		j;
	int		k;

	i = 1;
	k = 0;
	ft_bzero(options, options_size);
	while (args[i])
	{
		if (ft_strcmp(args[i], "--") == 0 || args[i][0] != '-' || !args[i][1])
			break ;
		j = 0;
		while (k < options_size - 1 && args[i][++j])
			if (!ft_strchr(options, args[i][j]))
				options[k++] = args[i][j];
		++i;
	}
	options[k] = '\0';
	return (i);
}

/*
** validate or invalidate an option buffer
** Params:
** - char *options : buffer containing the options
** - char *valid_set : a set of valid options characters
** Return: -1 if we found an invalid option, 0 if not
*/

int		builtin_validate_options(char *options, char *valid_set)
{
	size_t	i;

	i = 0;
	while (options[i])
	{
		if (!ft_strchr(valid_set, options[i]))
			return (-1);
		++i;
	}
	return (0);
}
