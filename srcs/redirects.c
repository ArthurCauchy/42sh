/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 13:54:17 by acauchy           #+#    #+#             */
/*   Updated: 2018/10/19 16:15:08 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "utils.h"
#include "redirects.h"

t_redirect	*new_redirect(char *left, char *right, t_token token)
{
	t_redirect	*redirect;

	if (!(redirect = (t_redirect*)malloc(sizeof(t_redirect))))
		exit_error("malloc() error");
	redirect->next = NULL;
	redirect->left = ft_strdup(left);
	redirect->right = ft_strdup(right);
	redirect->token = token;
	return (redirect);
}

void		delete_redirects(t_redirect *redirs)
{
	t_redirect	*prev;
	t_redirect	*cur;

	prev = NULL;
	cur = redirs;
	while (cur)
	{
		prev = cur;
		cur = cur->next;
		free(prev->left);
		free(prev->right);
		free(prev);
	}
}
