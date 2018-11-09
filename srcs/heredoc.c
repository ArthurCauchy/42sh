/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccharrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 15:32:52 by ccharrie          #+#    #+#             */
/*   Updated: 2018/11/09 15:57:00 by ccharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "utils.h"
#include "env.h"
#include "builtins.h"

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

int				init_heredoc(int fd, char delim)
{
	char	*new_line;
	char	*heredoc_line;
	int		save_in;
	
	new_line = NULL;
	heredoc_line = NULL;
	while (get_line("heredoc> ", new_line, line, env))
	{
		if (ft_strcmp(new_line, delim) == 0)
			break ;
		else if (/* getting ctrl-d */)
			break ;
		heredoc_line = ft_strjoin_free(heredoc_line, new_line);
		heredoc_line = ft_strjoin_free(heredoc_line, ft_strdup("\n"));
	}
	if (heredoc_line)
		ft_putstr_fd(heredoc_line, fd);
	else
		return (-1);
}
