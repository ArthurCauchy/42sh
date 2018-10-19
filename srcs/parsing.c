/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumenthi <lumenthi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 15:24:43 by lumenthi          #+#    #+#             */
/*   Updated: 2018/10/19 15:56:41 by lumenthi         ###   ########.fr       */
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
	if (elem == PIPE || elem == OR || elem == AND || elem == SEMICOL)
		return (1);
	return (0);
}

static int is_parsing_arg(t_token elem)
{
	if (elem == ARG || elem == LSHIFT || elem == LSHIFT_AMP || elem == LSHIFT2
	|| elem == RSHIFT || elem == RSHIFT2 || elem == RSHIFT_AMP)
		return (1);
	return (0);
}

t_error	init_error(void)
{
	t_error ret;

	ret.before = 0;
	ret.after = 0;
	ret.separator = NONE;
	ret.msg = NULL;
	return (ret);
}

static int	is_last(t_word *wordlist)
{
	if (wordlist->next == NULL)
		return (1);
	return (0);
}

int		parse_error(t_token token)
{
	ft_putstr_fd("Parse error near token `", 2);
	if (token == PIPE)
		ft_putstr_fd("|", 2);
	else if (token == OR)
		ft_putstr_fd("||", 2);
	else if (token == AND)
		ft_putstr_fd("&&", 2);
	else if (token == SEMICOL)
		ft_putstr_fd(";", 2);
	ft_putstr_fd("'\n", 2);
	return (0);
}

int		set_error(t_error *error, t_word *tmp)
{
	if (is_parsing_arg(tmp->token))
	{
		if (is_parsing_separator(error->separator))
		{
			if (error->before == 0)
				return (parse_error(error->separator));
			error->after = 1;
			*error = init_error();
			error->before = 1;
		}
		else
			error->before = 1;
	}
	else if (is_parsing_separator(tmp->token))
	{
		if (tmp->token == SEMICOL && is_parsing_separator(error->separator))
			return (parse_error(SEMICOL));
		error->separator = tmp->token;
	}
	if (is_last(tmp))
	{
		if (is_parsing_separator(error->separator) && (!error->before || !error->after) && error->separator != SEMICOL)
			return (parse_error(error->separator));
	}
	return (1);
}

t_parse_block* do_parsing(t_word *wordlist, char **errmsg)
{
	t_parse_block *parsing;
	t_word *tmp;
	t_parse_block *tmp_block;
	t_error error;

	parsing = NULL;
	tmp_block = NULL;
	error = init_error();
	tmp = wordlist;
	tmp_block = new_parse_block(NULL, NONE);
	(void)errmsg;
	while (tmp)
	{
		if (!set_error(&error, tmp))
			return (NULL);
		if (is_parsing_separator(tmp->token))
		{
			tmp_block->separator = tmp->token;
			block_push(&parsing, tmp_block);
			free_parse_block(&tmp_block);
			tmp_block = new_parse_block(NULL, NONE);
		}
		else if (tmp->next == NULL)
		{
			word_push(&tmp_block->wordlist, tmp);
			block_push(&parsing, tmp_block);
			free_parse_block(&tmp_block);
		}
		else
			word_push(&tmp_block->wordlist, tmp);
		tmp = tmp->next;
	}
// //		PRINT
// 		t_parse_block *display = parsing;
// 		while (display)
// 		{
// 			ft_putstr("BEGIN BLOCK\n");
// 			display_words(display->wordlist);
// 			if (display->separator == PIPE)
// 				printf("separator: PIPE\n");
// 			if (display->separator == NONE)
// 				printf("separator: NONE\n");
// 			display = display->next;
// 			ft_putstr("END BLOCK\n");
// 		}
// //		PRINT
	return (parsing);
}