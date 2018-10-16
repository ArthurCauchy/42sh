/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 16:11:38 by acauchy           #+#    #+#             */
/*   Updated: 2018/10/16 18:17:13 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include "parsing.h"

// actually run the command, TODO move it to a separate file
static void start_command()
{

}

int			pipeline_run(t_parse_block *pipeline)
{
	// TODO can the pipeline be NULL ? if yes check it first
	t_parse_block	*cur;
	int				pipefd[2];
	
	cur = pipeline;
	while (pipeline)
	{
		/* PIPE HANDLING
		if (cur != pipeline)
		{
			// redirect this command's STDIN to pipefd[0]
		}
		if (cur->next != NULL)
		{
			pipe(pipefd);
			// redirect this command's STDOUT to pipefd[1]
		}
		*/
		start_command();
		pipeline = pipeline->next;
	}
	// TODO clean pipes if commands not successful etc etc
}

// is this function actually the name as block_push or smthng in parsing.c ? the name is better for this use case tho
void		pipeline_add(t_parse_block **pipeline, t_parse_block *new)
{
	t_parse_block	*prev;
	t_parse_block	*cur;

	prev = NULL;
	cur = *pipeline;
	while (cur)
		cur = cur->next;
	if (prev)
		cur->next = new;
	else
		*pipeline = new;
}

// TEST INTRERPRET : just prints the blocks from parsing
int			do_interpret(t_parse_block *parsed)
{
	t_parse_block	*cur;
	t_word			*wordlist;

	cur = parsed;
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
int			do_interpret(t_parse_block *parsed)
{
	int				ret;
	t_parse_block	*pipeline;
	t_parse_block	*cur;

	ret = 0;
	pipeline = NULL;
	cur = *parsed;
	while (cur)
	{
		pipeline_add(&pipeline, cur);
		if (parsed->token == PIPE)
			continue;
		ret = pipeline_run(pipeline);
		if ((ret != 0 && cur->token == AND)
				|| (ret == 0 && cur->token == OR))
			return (ret);
		pipeline = NULL; // pipeline clear
		cur = cur->next;
	}
	return (ret);
}
