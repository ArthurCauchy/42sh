/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumenthi <lumenthi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 15:24:43 by lumenthi          #+#    #+#             */
/*   Updated: 2018/10/16 14:54:15 by lumenthi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "libft.h"
#include <stdio.h> //for printf, remove after
#include <stdlib.h>

void display_words(t_word *words)
{
	t_word *tmp = words;
	ft_putstr("BEGIN DISPLAY\n");
	while (tmp)
	{
		ft_putstr("words: ");
		ft_putendl(tmp->str);
		tmp = tmp->next;
	}
	ft_putstr("END DISPLAY\n");
}

void word_push(t_word **wordlist, t_word *new_word)
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

void block_push(t_parse_block **blocklist, t_parse_block *new_block)
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
	cur->wordlist = new_block->wordlist;
	cur->separator = new_block->separator;
	cur->next = NULL;
	if (prev)
		prev->next = cur;
	else
		*blocklist = cur;
}

int	is_parsing_separator(t_token elem)
{
	if (elem == PIPE || elem == OR || elem == AND || elem == SEMICOL ||
		elem == NONE)
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
	tmp_block = (t_parse_block *)malloc(sizeof(t_parse_block));
	tmp_block->wordlist = NULL;
	tmp_block->next = NULL;
	(void)errmsg;
	while (tmp)
	{
		if (is_parsing_separator(tmp->token))
		{
			tmp_block->separator = tmp->token;
			block_push(&parsing, tmp_block);
		}
		else
			word_push(&tmp_block->wordlist, tmp);
		tmp = tmp->next;
	}
	//	PRINT
		// while (tmp_block)
		// {
		// 	display_words(tmp_block->wordlist);
		// 	if (tmp_block->separator == PIPE)
		// 		printf("separator: PIPE\n");
		//  	tmp_block = tmp_block->next;
		// }
	//	PRINT
	free(tmp_block);
	return (parsing);
}