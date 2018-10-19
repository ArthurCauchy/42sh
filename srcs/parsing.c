/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumenthi <lumenthi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 15:24:43 by lumenthi          #+#    #+#             */
/*   Updated: 2018/10/19 12:00:02 by lumenthi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "libft.h"
#include <stdio.h> //for printf, remove after
#include <stdlib.h>

void display_words(t_word *words) //display, remove after
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

static int	is_parsing_separator(t_token elem)
{
	if (elem == PIPE || elem == OR || elem == AND || elem == SEMICOL ||
		elem == NONE)
		return (1);
	return (0);
}

t_parse_block* do_parsing(t_word *wordlist, char **errmsg)
{
	t_parse_block *parsing;
	t_word *tmp;
	t_parse_block *tmp_block;

	parsing = NULL;
	tmp_block = NULL;
	tmp = wordlist;
	tmp_block = new_parse_block(NULL, NONE);
	(void)errmsg;
	while (tmp)
	{
		if (tmp->next == NULL)
		{
			word_push(&tmp_block->wordlist, tmp);
			block_push(&parsing, tmp_block);
			free_parse_block(&tmp_block);
		}
		else if (is_parsing_separator(tmp->token))
		{
			tmp_block->separator = tmp->token;
			block_push(&parsing, tmp_block);
			free_parse_block(&tmp_block);
			tmp_block = new_parse_block(NULL, NONE);
		}
		else
			word_push(&tmp_block->wordlist, tmp);
		tmp = tmp->next;
	}
//		PRINT
		t_parse_block *display = parsing;
		while (display)
		{
			ft_putstr("BEGIN BLOCK\n");
			display_words(display->wordlist);
			if (display->separator == PIPE)
				printf("separator: PIPE\n");
			if (display->separator == NONE)
				printf("separator: NONE\n");
			display = display->next;
			ft_putstr("END BLOCK\n");
		}
//		PRINT
	return (parsing);
}