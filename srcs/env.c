/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 10:48:57 by acauchy           #+#    #+#             */
/*   Updated: 2018/08/20 17:33:26 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "utils.h"
#include "env.h"

void	print_env(t_env **env)
{
	t_env	*cur;

	cur = *env;
	while (cur)
	{
		ft_fminiprint(1, "%l0s%=%l0s%\n", cur->key, cur->value);
		cur = cur->next;
	}
}

char	*read_from_env(t_env **env, char *key)
{
	t_env	*cur;

	cur = *env;
	while (cur)
	{
		if (ft_strcmp(cur->key, key) == 0)
			return (ft_strdup(cur->value));
		cur = cur->next;
	}
	return (NULL);
}

char	**env_to_array(t_env **env)
{
	t_env	*cur;
	char	**array;
	size_t	size;
	size_t	i;

	cur = *env;
	size = 0;
	while (cur)
	{
		++size;
		cur = cur->next;
	}
	if (!(array = (char**)malloc((size + 1) * sizeof(char*))))
		exit_error("env_to_array malloc() error");
	cur = *env;
	i = 0;
	while (cur)
	{
		array[i++] = ft_strjoin_free(ft_strjoin(cur->key, "="),
				ft_strdup(cur->value));
		cur = cur->next;
	}
	array[i++] = NULL;
	return (array);
}
