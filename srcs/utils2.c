/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 11:34:35 by acauchy           #+#    #+#             */
/*   Updated: 2018/10/22 17:44:46 by ccharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "global.h"

void	print_n_free_errmsg(char **errmsg)
{
	ft_putendl_fd(*errmsg, 2);
	free(*errmsg);
	*errmsg = NULL;
}

char	*get_alias_value(char *key)
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
