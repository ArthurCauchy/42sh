/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 14:21:35 by acauchy           #+#    #+#             */
/*   Updated: 2017/11/17 15:12:03 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*lst2;
	t_list	*ptr;

	if (!f || !lst)
		return (NULL);
	ptr = f(lst);
	if (!ptr || !(lst2 = ft_lstnew(ptr->content, ptr->content_size)))
		return (NULL);
	if (lst->next)
		lst2->next = ft_lstmap(lst->next, f);
	return (lst2);
}
