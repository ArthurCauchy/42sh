/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 16:11:38 by acauchy           #+#    #+#             */
/*   Updated: 2018/10/17 12:21:40 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include "utils.h"
#include "builtins.h"
#include "parsing.h"
#include "global.h"

// actually run the command, TODO move it to a separate file
static int	start_command(t_word *cmd_args)
{
	int			ret;
	t_builtin	*builtin;
	char		**args;
	
	args = ft_memalloc(sizeof(char*) * PARAMS_MAX);
	if ((builtin = search_builtin(cmd_args->str)))
	{
		// apply redirects builtin-style
		arglist_to_array(cmd_args, args);
		ret = builtin->func(&g_env, args);
	}
	else
	{
		ft_putendl_fd("Not a builtin.", 2);
		//apply redirects normal
		return (1);
	}
	delete_args(args);
	return (ret);
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

// TEST INTRERPRET : just prints the blocks from parsing
/*int			do_interpret(t_parse_block *parsed)
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
	return (0);
}*/

// real fct
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
			pipeline = NULL; // pipeline clear
		}
		cur = cur->next;
	}
	return (ret);
}
