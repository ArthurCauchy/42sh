/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 16:11:38 by acauchy           #+#    #+#             */
/*   Updated: 2018/10/15 17:19:46 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	do_interpret(t_parse_block *parsed)
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
