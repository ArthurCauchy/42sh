/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccharrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 15:32:52 by ccharrie          #+#    #+#             */
/*   Updated: 2018/11/09 21:26:10 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include "utils.h"
#include "env.h"
#include "builtins.h"
#include "heredoc.h"
#include "redirects.h"
#include "line_edit.h"
#include "global.h"

int			open_heredoc_file(char *filename, char **errmsg)
{
	int flags;
	int fd;

	flags = O_WRONLY | O_CREAT | O_EXCL | O_TRUNC;
	fd = open(filename, flags, 0600);
	if (fd < 0)
	{
		*errmsg = ft_strdup(filename);
		*errmsg = ft_strjoin_free(*errmsg, ft_strdup(": "));
		*errmsg = ft_strjoin_free(*errmsg, ft_strdup(strerror(errno)));
	}
	return (fd);
}

static int	write_heredoc(int fd, char *delim)
{
	char	*new_line;
	char	ctrl;

	ctrl = 0;
	while (42)
	{
		new_line = ask_for_input(HEREDOC_PROMPT, &ctrl);
		if (ctrl != 'd' && new_line == NULL)
			return (-1);
		if (ctrl == 'd' || ft_strcmp(new_line, delim) == 0)
		{
			free(new_line);
			break ;
		}
		ft_putendl_fd(new_line, fd);
		free(new_line);
	}
	return (0);
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

	init_heredoc_fds();
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
