/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_alias.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 17:05:12 by acauchy           #+#    #+#             */
/*   Updated: 2018/10/19 17:12:08 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "env.h"

int	builtin_alias(t_env **env, char **args)
{
	(void)env;
	(void)args;
	ft_putendl("ALIAS BUILTIN");
	return (0);
}
