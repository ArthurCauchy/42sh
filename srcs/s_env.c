/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_env.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 11:03:45 by acauchy           #+#    #+#             */
/*   Updated: 2018/08/20 17:30:53 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "utils.h"
#include "env.h"

static t_env	*create_entry(char *key, char *value)
{
	t_env	*new;

	if (!(new = (t_env*)malloc(sizeof(t_env))))
		exit_error("env create_entry() malloc error");
	if (!(new->key = key))
		exit_error("env create_entry() 'key' malloc error");
	if (!(new->value = value))
		exit_error("env create_entry() 'value' malloc error");
	new->next = NULL;
	return (new);
}

void			clear_env(t_env *env)
{
	t_env	*prev;

	prev = NULL;
	while (env)
	{
		prev = env;
		env = env->next;
		free(prev->key);
		free(prev->value);
		free(prev);
	}
}

void			set_env(t_env **head, char *key, char *value)
{
	t_env	*new_entry;
	t_env	*cur;

	cur = *head;
	if (!*head)
		*head = create_entry(key, value);
	else
		while (cur)
		{
			if (ft_strcmp(cur->key, key) == 0)
			{
				free(cur->key);
				free(cur->value);
				cur->key = key;
				cur->value = value;
				return ;
			}
			if (!cur->next)
			{
				new_entry = create_entry(key, value);
				cur->next = new_entry;
				return ;
			}
			cur = cur->next;
		}
}

void			unset_env(t_env **head, char *key)
{
	t_env	*cur;
	t_env	*prev;
	t_env	*tmp;

	cur = *head;
	prev = NULL;
	while (cur)
	{
		if (ft_strcmp(cur->key, key) == 0)
		{
			if (prev)
				prev->next = cur->next;
			tmp = cur->next;
			if (cur == *head)
				*head = cur->next;
			ft_multifree(3, cur->key, cur->value, cur);
			cur = tmp;
		}
		else
		{
			prev = cur;
			cur = cur->next;
		}
	}
}

t_env			*copy_env(t_env **env)
{
	t_env	*cur;
	t_env	*new_head;
	t_env	*new_cur;
	t_env	*new_prev;

	cur = *env;
	new_head = NULL;
	new_prev = NULL;
	while (cur)
	{
		if (!(new_cur = create_entry(ft_strdup(cur->key),
						ft_strdup(cur->value))))
			exit_error("error creating new env entry in env_copy");
		if (!new_head)
			new_head = new_cur;
		if (new_prev)
			new_prev->next = new_cur;
		new_prev = new_cur;
		cur = cur->next;
	}
	return (new_head);
}
