/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 16:11:38 by acauchy           #+#    #+#             */
/*   Updated: 2018/10/17 17:14:05 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include "utils.h"
#include "builtins.h"
#include "parsing.h"
#include "global.h"

// TODO make a file like word.c but for parse_block
static t_parse_block*	clone_parse_block(t_parse_block *orig)
{
	return(new_parse_block(copy_wordlist(orig->wordlist), orig->separator));
}

// debug start_command : actually just prints the args
static int	start_command(t_word *cmd_args)
{
	t_word	*cur;

	cur = cmd_args;
	ft_putstr("Starting process : '");
	while (cur)
	{
		if (cur != cmd_args)
			ft_putchar(' ');
		ft_putstr(cur->str);
		cur = cur->next;
	}
	ft_putstr("\'\n");
	return (0);
}

static int	pipeline_run(t_parse_block *pipeline)
{
	int	ret;
	// TODO can the pipeline be NULL ? if yes check it first
	t_parse_block	*cur;
	//int				pipefd[2];

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
		ret = start_command(pipeline->wordlist);
		pipeline = pipeline->next;
	}
	// TODO clean pipes if commands not successful etc etc
	return (ret);
}

static void	pipeline_add(t_parse_block **pipeline, t_parse_block *new)
{
	t_parse_block	*prev;
	t_parse_block	*cur;

	prev = NULL;
	cur = *pipeline;
	while (cur)
		cur = cur->next;
	if (prev)
		cur->next = clone_parse_block(new);
	else
		*pipeline = clone_parse_block(new);
}

int			do_interpret(t_parse_block *parsed)
{
	int				ret;
	t_parse_block	*pipeline;
	t_parse_block	*cur;

	ret = 0;
	pipeline = NULL;
	cur = parsed;
	while (cur)
	{
		pipeline_add(&pipeline, cur);
		if (parsed->separator != PIPE)
		{
			ret = pipeline_run(pipeline);
			free_parse_block(&pipeline);
			if ((ret != 0 && cur->separator == AND)
					|| (ret == 0 && cur->separator == OR))
				return (ret);
		}
		cur = cur->next;
	}
	return (ret);
}
