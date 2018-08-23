/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/04 10:29:04 by acauchy           #+#    #+#             */
/*   Updated: 2018/08/23 11:36:00 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "utils.h"
#include "lexing.h"

t_word	*new_word(t_token token, char *str)
{
	t_word	*new;
	char	*dup_str;

	if (!(new = (t_word*)malloc(sizeof(t_word))))
		exit_error("malloc() error");
	if (!(dup_str = ft_strdup(str)))
		exit_error("ft_strdup() error");
	new->token = token;
	new->str = dup_str;
	new->next = NULL;
	return (new);
}

void	remove_word(t_word **wordlist, t_word *word)
{
	t_word	*prev;
	t_word	*cur;

	if (!word)
		return ;
	prev = NULL;
	cur = *wordlist;
	while (cur)
	{
		if (cur == word)
		{
			if (prev)
				prev->next = cur->next;
			if (cur == *wordlist)
				*wordlist = cur->next;
			if (cur->str)
				free(cur->str);
			free(cur);
			break ;
		}
		prev = cur;
		cur = cur->next;
	}
}

void	delete_wordlist(t_word **head)
{
	t_word	*cur;
	t_word	*prev;

	cur = *head;
	prev = NULL;
	while (cur)
	{
		if (cur->str)
			free(cur->str);
		prev = cur;
		cur = cur->next;
		free(prev);
	}
	*head = NULL;
}
