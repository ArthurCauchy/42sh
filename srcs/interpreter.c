/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 16:11:38 by acauchy           #+#    #+#             */
/*   Updated: 2018/10/16 11:56:34 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/*
** Returns the appropriate interpreter fct corresponding to the parameter 'token'
*/

/*static int	get_interpret_fct(t_token token)
{
	if (token == SEMICOL)
}*/

// TEST INTRERPRET : just prints the blocks from parsing
int			do_interpret(t_parse_block *parsed)
{
	t_parse_block	*cur;
	t_wordlist		*wordlist;

	cur = *parsed;
	while (cur)
	{
		wordlist = cur->wordlist;
		while (wordlist)
		{
			ft_putstr(wordlist->str);
			if (wordlist->next)
				ft_putchar('\n');
			else
				ft_putchar(' ');
			wordlist = wordlist->next;
		}
		cur = cur->next;
	}
	return (/*status code*/0);
}

// real fct
/*int			do_interpret(t_parse_block *parsed)
{
	t_parse_block	*cur;

	cur = *parsed;
	while (cur)
	{
		if (parsed->token != PIPE)
			// start commands in pipe
		else
			// add to pipeline

		cur = cur->next;
	}
	return (0);
}*/
