/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumenthi <lumenthi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 15:24:43 by lumenthi          #+#    #+#             */
/*   Updated: 2018/10/15 18:00:59 by lumenthi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <stdio.h> //for printf, remove after

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

t_parse_block* do_parsing(t_word *wordlist, char **errmsg)
{
	t_parse_block *parsing;
	t_word *tmp;
	t_word *dest;

	parsing = NULL;
	tmp = wordlist;
	(void)errmsg;
	while (tmp)
	{
		if (parsing == NULL)
			parsing = (t_parse_block *)malloc(sizeof(t_parse_block));
		if (dest == NULL)
			dest = (t_word *)malloc(sizeof(t_word));
		tmp = tmp->next;
		parsing->next = NULL;
	}
	return (parsing);
}