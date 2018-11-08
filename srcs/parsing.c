/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumenthi <lumenthi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 15:24:43 by lumenthi          #+#    #+#             */
/*   Updated: 2018/11/08 11:27:25 by lumenthi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "libft.h"
#include <stdlib.h>

static int	error_parsing(t_error *error, t_word **tmp,
t_parse_block **tmp_block, t_parse_block **parsing)
{
	int ret;

	if (!(ret = set_error(error, *tmp)))
	{
		free_parse_block(tmp_block);
		free_parse_block(parsing);
		return (-1);
	}
	else if (ret == 2)
	{
		word_push(&(*tmp_block)->wordlist, *tmp);
		block_push(parsing, *tmp_block);
		free_parse_block(tmp_block);
		return (1);
	}
	return (0);
}

static void	next_parsing(t_word **tmp, t_parse_block **tmp_block,
t_parse_block **parsing)
{
	if (is_parsing_separator((*tmp)->token))
	{
		(*tmp_block)->separator = (*tmp)->token;
		block_push(parsing, *tmp_block);
		free_parse_block(tmp_block);
		if ((*tmp)->next != NULL)
			*tmp_block = new_parse_block(NULL, NONE);
	}
	else if ((*tmp)->next == NULL)
	{
		word_push(&(*tmp_block)->wordlist, *tmp);
		block_push(parsing, *tmp_block);
		free_parse_block(tmp_block);
	}
	else
		word_push(&(*tmp_block)->wordlist, *tmp);
	*tmp = (*tmp)->next;
}

int			do_parsing(t_word *wordlist, t_parse_block **parsing, char **errmsg)
{
	t_word			*tmp;
	t_parse_block	*tmp_block;
	t_error			error;
	int				ret;

	tmp_block = NULL;
	error = init_error();
	tmp = wordlist;
	tmp_block = new_parse_block(NULL, NONE);
	(void)errmsg;
	while (tmp)
	{
		if ((ret = error_parsing(&error, &tmp, &tmp_block, parsing)) != 0)
			return (ret);
		next_parsing(&tmp, &tmp_block, parsing);
	}
	return (parsing == NULL ? -1 : 0);
}
