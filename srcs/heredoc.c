/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccharrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 15:32:52 by ccharrie          #+#    #+#             */
/*   Updated: 2018/11/09 16:21:05 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include "utils.h"
#include "env.h"
#include "builtins.h"
#include "heredoc.h"

void	init_heredoc(t_line *line, t_env *env, char *eof)
{
	char	*new_line;
	char	*heredoc_line;
	int		fd;
	int		save_in;

	new_line = NULL;
	heredoc_line = NULL;
	fd = open(".heredoc", O_WRONLY | O_CREAT | O_TRUNC);
	while (get_line("heredoc> ", new_line, line, env))
	{
		if (ft_strcmp(new_line, eof) == 0)
			break ;
		heredoc_line = ft_strjoin_free(heredoc_line, new_line);
		heredoc_line = ft_strjoin_free(heredoc_line, "\n");
	}
	ft_putstr_fd(heredoc_line, fd);
	//	execute_command(t_line *line);
}

static int	ask_input_heredoc(t_word *wordlist, char **errmsg)
{
	int	heredoc_fd;

	heredoc_fd = open_heredoc_file("/tmp/heredoc-tmp", errmsg);
	if (heredoc_fd == -1)
		return (-1);
	if (write_heredoc(heredoc_fd, wordlist->next->str) == -1)
	{
		close(heredoc_fd);
		unlink("/tmp/heredoc-tmp");
		return (-1);
	}
	close(heredoc_fd);
	return (0);
}

int			apply_heredocs(t_word *wordlist, char **errmsg)
{
	int	heredoc_fd;

	while (wordlist)
	{
		if (wordlist->token == LSHIFT2)
		{
			if (!wordlist->next || wordlist->next->token != ARG)
			{
				*errmsg = ft_strdup("Missing name for redirect.");
				return (-1);
			}
			if (ask_input_heredoc(wordlist, errmsg) == -1)
				return (-1);
			heredoc_fd = open_file_fd("/tmp/heredoc-tmp", 0, 0, errmsg);
			if (heredoc_fd == -1)
				return (-1);
			unlink("/tmp/heredoc-tmp");
			free(wordlist->next->str);
			register_heredoc_fd(heredoc_fd);
			wordlist->next->str = ft_itoa(heredoc_fd);
		}
		wordlist = wordlist->next;
	}
	return (0);
}
