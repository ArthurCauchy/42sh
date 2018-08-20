/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 13:35:57 by acauchy           #+#    #+#             */
/*   Updated: 2017/11/20 09:57:54 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd(t_list **alst, t_list *new)
{
	if (!new)
		return ;
	if (!alst)
	{
		new->next = (void*)0;
		return ;
	}
	else if (!*alst)
		new->next = (void*)0;
	else
		new->next = *alst;
	*alst = new;
}
