/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/04 10:29:04 by acauchy           #+#    #+#             */
/*   Updated: 2018/11/09 11:20:30 by acauchy          ###   ########.fr       */
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

t_word	*copy_wordlist(t_word *wordlist)
{
	t_word	*new;
	t_word	*cur_orig;
	t_word	*prev_new;
	t_word	*cur_new;

	new = NULL;
	cur_orig = wordlist;
	prev_new = NULL;
	cur_new = NULL;
	while (cur_orig)
	{
		cur_new = new_word(cur_orig->token, cur_orig->str);
		if (prev_new)
			prev_new->next = cur_new;
		else
			new = cur_new;
		prev_new = cur_new;
		cur_orig = cur_orig->next;
	}
	return (new);
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
