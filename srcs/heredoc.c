/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccharrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 15:32:52 by ccharrie          #+#    #+#             */
/*   Updated: 2018/11/09 17:30:09 by acauchy          ###   ########.fr       */
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

/*static char 	open_heredoc_file(int *fd)
  {
  if ((fd = open(".heredoc", O_WRONLY | O_CREAT | O_TRUNC)) < 0)
  return (".heredoc");
  else if ((fd = open("/tmp/.heredoc", O_WRONLY | O_CREAT | O_TRUNC)) < 0)
  return ("/tmp/.heredoc");
//	function to get HOME env variable
else if ((fd = open("HOME/.heredoc", O_WRONLY | O_CREAT | O_TRUNC)) < 0)
return ("HOME/.heredoc");
else
return (NULL);
}*/

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

int				write_heredoc(int fd, char *delim)
{
	char	*new_line;
	char	*heredoc_line;

	new_line = NULL;
	heredoc_line = NULL;
	while ((new_line = ask_for_input(HEREDOC_PROMPT)))
	{
		if (ft_strcmp(new_line, delim) == 0)
			break ;
		else if (0/* getting ctrl-d */)
			break ;
		ft_putendl_fd(new_line, 2);
		heredoc_line = ft_strjoin_free(heredoc_line, new_line);
		heredoc_line = ft_strjoin_free(heredoc_line, ft_strdup("\n"));
	}
	if (heredoc_line)
	{
		ft_putstr_fd(heredoc_line, fd);
	}
	else
		return (-1);
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
