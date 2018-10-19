/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 10:59:12 by acauchy           #+#    #+#             */
/*   Updated: 2018/10/19 16:15:10 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "redirects.h"

static int	is_redirection(t_token token)
{
	if (token == LSHIFT
			|| token == LSHIFT_AMP
			|| token == LSHIFT2
			|| token == RSHIFT
			|| token == RSHIFT_AMP
			|| token == RSHIFT2)
		return (1);
	return (0);
}

static char	*extract_left_digits(char *str)
{
	char	buff[64];
	size_t	i;

	ft_strncpy(buff, str, 64);
	i = 0;
	while (i < 64)
	{
		if (!ft_isdigit(buff[i]))
		{
			buff[i] = '\0';
			break ;
		}
		++i;
	}
	return (ft_strdup(buff));
}

void		add_redirect(t_redirect **redirs,
		char *left, char *right, t_token token)
{
	t_redirect	*redirect;
	t_redirect	*cur;

	redirect = new_redirect(left, right, token);
	cur = *redirs;
	if (!cur)
		*redirs = redirect;
	else
	{
		while (cur->next)
			cur = cur->next;
		cur->next = redirect;
	}
}

static void	remove_redir(t_word **arglist, t_word *token, t_word *left)
{
	remove_word(arglist, token);
	remove_word(arglist, left);
}

int			analyze_redirects(t_word **arglist,
		t_redirect **redirs, char **errmsg)
{
	t_word	*cur;
	t_word	*next;
	char	*left;

	cur = *arglist;
	while (cur)
	{
		if (is_redirection(cur->token))
		{
			next = cur->next;
			if (!next || next->token != ARG)
			{
				*errmsg = ft_strdup("Missing name for redirect.");
				return (-1);
			}
			left = extract_left_digits(cur->str);
			add_redirect(redirs, left, next->str, cur->token);
			free(left);
			remove_redir(arglist, cur, next);
			cur = *arglist;
		}
		else
			cur = cur->next;
	}
	return (0);
}
