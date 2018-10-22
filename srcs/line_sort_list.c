/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_rev_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saxiao <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 12:45:28 by saxiao            #+#    #+#             */
/*   Updated: 2018/10/22 12:25:41 by saxiao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edit.h"

void			del_one_list(t_autolist **list, t_autolist *onelt)
{
	t_autolist	*del;
	t_autolist	*pre;
	t_autolist	*temp;

	del = *list;
	pre = NULL;
	while (del && ft_strcmp(del->name, onelt->name))
	{
		pre = del;
		del = del->next;
	}
	if (!pre)
	{
		temp = *list;
		*list = (*list)->next;
		temp->next = NULL;
	}
	else
	{
		pre->next = del->next;
		del->next = NULL;
	}
}

void			sort_list(t_autolist **list)
{
	t_autolist	*cp;
	t_autolist	*add;
	t_autolist	*re;

	re = NULL;
	while (*list)
	{
		add = *list;
		cp = (*list)->next;
		while (cp)
		{
			if (ft_strcmp(cp->name, add->name) < 0)
				add = cp;
			cp = cp->next;
		}
		re = add_one_list(re, add);
		del_one_list(list, add);
	}
	*list = re;
}
