/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpushback.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 09:57:01 by acauchy           #+#    #+#             */
/*   Updated: 2018/01/17 14:48:03 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstpushback(t_list **alst, t_list *new)
{
	t_list	*elem;

	if (!new || !alst)
		return (NULL);
	if (*alst)
	{
		elem = *alst;
		while (elem->next)
			elem = elem->next;
		elem->next = new;
	}
	else
		*alst = new;
	return (new);
}
