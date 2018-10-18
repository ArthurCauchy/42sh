/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 16:11:38 by acauchy           #+#    #+#             */
/*   Updated: 2018/10/18 20:22:26 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/wait.h>
#include "libft.h"
#include "utils.h"
#include "builtins.h"
#include "parsing.h"
#include "starter.h"
#include "global.h"

// TODO make a file like word.c but for parse_block
static t_parse_block*	clone_parse_block(t_parse_block *orig)
{
	return (new_parse_block(copy_wordlist(orig->wordlist), orig->separator));
}

// debug start_command : actually just prints the args
/*static int	start_command(t_word *cmd_args)
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
}*/

// NOTE : the pipeline should always contain at least 1 program
static int	pipeline_run(t_parse_block *pipeline)
{
	static int	child_fds[4096]; // TODO create a define for max process in pipe
	t_process	*proc;
	int			pl_size;
	int			i;
	int			status;
	int			ret;
	//int				pipefd[2];

	ft_bzero(child_fds, 4096 * sizeof(int));
	pl_size = 0;
	while (pipeline)
	{
		proc = new_process(arglist_to_array(pipeline->wordlist));
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
		child_fds[pl_size++] = start_process(proc, pipeline->next ? 1 : 0);
		delete_process(proc);
		pipeline = pipeline->next;
	}
	// TODO actually one waitpid could be enough if all the subprocesses are in the same pgid
	i = 0;
	while (i < pl_size)
	{
		if (child_fds[i] <= 0)// IF NOT ONLY A BUILTIN
			ret = -child_fds[i];
		else
		{
			waitpid(child_fds[i], &status, WUNTRACED); // TODO check WUNTRACED useful ?
			ret = WEXITSTATUS(status);
		}
		++i;
	}
	// TODO clean pipes if commands not successful etc etc
	return (ret);
}

static void	pipeline_add(t_parse_block **pipeline, t_parse_block *new) // TODO optimize, don't need 2 variables to do that
{
	t_parse_block	*prev;
	t_parse_block	*cur;

	prev = NULL;
	cur = *pipeline;
	while (cur)
	{
		prev = cur;
		cur = cur->next;
	}
	if (prev)
		prev->next = clone_parse_block(new);
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
	free_parse_block(&pipeline);
	return (ret);
}
