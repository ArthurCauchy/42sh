/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 11:34:35 by acauchy           #+#    #+#             */
/*   Updated: 2018/11/08 18:43:28 by ccharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "global.h"

void		print_n_free_errmsg(char **errmsg)
{
	ft_putendl_fd(*errmsg, 2);
	free(*errmsg);
	*errmsg = NULL;
}

char		*get_alias_value(char *key)
{
	t_alias *cur;

	cur = g_aliases;
	while (cur)
	{
		if (ft_strcmp(cur->key, key) == 0)
			return (cur->value);
		cur = cur->next;
	}
	return (NULL);
}

int			check_alias_forbid_char(char *value)
{
	char	*setter;

	if ((setter = ft_strchr(value, '\''))
			|| (setter = ft_strchr(value, '\"'))
			|| (setter = ft_strchr(value, '\\')))
	{
		ft_putstr("alias error : '");
		ft_putchar(*setter);
		ft_putendl("' is not allowed inside the alias value");
		return (-1);
	}
	return (0);
}
