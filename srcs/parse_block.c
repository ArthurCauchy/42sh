/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_block.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumenthi <lumenthi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 11:52:21 by lumenthi          #+#    #+#             */
/*   Updated: 2018/11/09 11:21:57 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lexing.h"
#include "parsing.h"
#include <stdlib.h>

void			word_push(t_word **wordlist, t_word *new_word)
{
	t_word *cur;
	t_word *prev;

	cur = *wordlist;
	prev = NULL;
	while (cur)
	{
		prev = cur;
		cur = cur->next;
	}
	cur = (t_word *)malloc(sizeof(t_word));
	cur->token = new_word->token;
	cur->str = ft_strdup(new_word->str);
	cur->next = NULL;
	if (prev)
		prev->next = cur;
	else
		*wordlist = cur;
}

static void		word_push_all(t_word **wordlist, t_word *new_words)
{
	t_word *tmp_new;

	tmp_new = new_words;
	while (tmp_new)
	{
		word_push(wordlist, tmp_new);
		tmp_new = tmp_new->next;
	}
}

void			block_push(t_parse_block **blocklist, t_parse_block *new_block)
{
	t_parse_block *cur;
	t_parse_block *prev;

	cur = *blocklist;
	prev = NULL;
	while (cur)
	{
		prev = cur;
		cur = cur->next;
	}
	cur = (t_parse_block *)malloc(sizeof(t_parse_block));
	cur->wordlist = NULL;
	cur->separator = new_block->separator;
	word_push_all(&cur->wordlist, new_block->wordlist);
	cur->next = NULL;
	if (prev)
		prev->next = cur;
	else
		*blocklist = cur;
}

void			free_parse_block(t_parse_block **parse)
{
	t_parse_block *cur;
	t_parse_block *prev;

	cur = *parse;
	prev = NULL;
	while (cur)
	{
		delete_wordlist(&(cur)->wordlist);
		prev = cur;
		cur = cur->next;
		free(prev);
	}
	*parse = NULL;
}

t_parse_block	*new_parse_block(t_word *word, t_token separator)
{
	t_parse_block *ret;

	ret = (t_parse_block *)malloc(sizeof(t_parse_block));
	ret->wordlist = word;
	ret->separator = separator;
	ret->next = NULL;
	return (ret);
}
