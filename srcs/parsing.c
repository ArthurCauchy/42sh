/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumenthi <lumenthi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 15:24:43 by lumenthi          #+#    #+#             */
/*   Updated: 2018/10/16 11:59:39 by lumenthi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "libft.h"
#include <stdio.h> //for printf, remove after
#include <stdlib.h>

void word_push(t_word *wordlist, t_word *new_word)
{
	t_word *tmp;

	tmp = wordlist;
	while (tmp)
		tmp = tmp->next;
	tmp = (t_word *)malloc(sizeof(t_word));
	tmp->token = new_word->token;
	tmp->str = ft_strdup(new_word->str);
	tmp->next = NULL;
}

void block_push(t_parse_block *blocklist, t_parse_block *new_block)
{
	t_parse_block *tmp;

	tmp = blocklist;
	while (tmp)
		tmp = tmp->next;
	tmp = (t_parse_block *)malloc(sizeof(t_parse_block));
	tmp->wordlist = new_block->wordlist;
	tmp->separator = new_block->separator;
	tmp->next = NULL;
}

int	is_separator(t_token elem)
{
	if (elem == PIPE || elem == OR || elem == AND || elem == SEMICOL)
		return (1);
	return (0);
}

t_parse_block* do_parsing(t_word *wordlist, char **errmsg)
{
	t_parse_block *parsing;
	t_word *tmp_word;
	t_word *tmp;
	t_parse_block *tmp_block;

	parsing = NULL;
	tmp_word = NULL;
	tmp_block = NULL;
	tmp = wordlist;
	(void)errmsg;
	while (tmp)
	{
		if (is_separator(tmp->token))
		{
			tmp_block->separator = tmp->token;
			block_push(parsing, tmp_block);
		}
		word_push(tmp_block->wordlist, tmp);
		tmp = tmp->next;
	}
	return (parsing);
}