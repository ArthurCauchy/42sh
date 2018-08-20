/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_l_simplify.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 10:06:00 by acauchy           #+#    #+#             */
/*   Updated: 2018/08/20 17:55:02 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "builtins.h"

void	simplify_path_dot(t_list **list)
{
	t_list	*prev;
	t_list	*cur;
	t_list	*next;

	prev = NULL;
	cur = *list;
	while (cur)
	{
		next = cur->next;
		if (ft_strcmp(*((char**)cur->content), ".") == 0)
		{
			if (prev)
				prev->next = cur->next;
			else
				*list = cur->next;
			free(*((char**)cur->content));
			free(cur->content);
			free(cur);
		}
		else
			prev = cur;
		cur = next;
	}
}

void	simplify_path_dotdot(t_list **list)
{
	t_list	*prev_dir;
	t_list	*cur;

	prev_dir = NULL;
	cur = *list;
	while (cur)
	{
		if (ft_strcmp(*((char**)cur->content), "..") != 0
				&& ft_strcmp(*((char**)cur->content), "/") != 0)
			prev_dir = cur;
		if (ft_strcmp(*((char**)cur->content), "..") == 0)
		{
			if (prev_dir)
				remove_from_compo_lst(list, prev_dir);
			remove_from_compo_lst(list, cur);
			prev_dir = NULL;
			cur = *list;
			continue;
		}
		cur = cur->next;
	}
}

void	simplify_path_slash(t_list **list)
{
	t_list	*prev;
	t_list	*cur;

	prev = NULL;
	cur = *list;
	while (cur)
	{
		if (prev && ((ft_strchr(*((char**)prev->content), '/')) || !cur->next)
				&& (ft_strchr(*((char**)cur->content), '/')))
		{
			prev->next = cur->next;
			free(*((char**)cur->content));
			free(cur->content);
			free(cur);
			prev = NULL;
			cur = *list;
			continue;
		}
		prev = cur;
		cur = cur->next;
	}
}
