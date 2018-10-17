/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 16:11:38 by acauchy           #+#    #+#             */
/*   Updated: 2018/10/17 15:33:37 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include "utils.h"
#include "builtins.h"
#include "parsing.h"
#include "global.h"

// debug start_command : actualy just prints the args
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

// is this function actually the name as block_push or smthng in parsing.c ? the name is better for this use case tho
static void	pipeline_add(t_parse_block **pipeline, t_parse_block *new)
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
			if ((ret != 0 && cur->separator == AND)
					|| (ret == 0 && cur->separator == OR))
				return (ret);
			pipeline = NULL;
		}
		cur = cur->next;
	}
	return (ret);
}
