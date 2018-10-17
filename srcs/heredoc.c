/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccharrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 15:32:52 by ccharrie          #+#    #+#             */
/*   Updated: 2018/10/15 16:53:15 by ccharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "utils.h"
#include "env.h"
#include "builtins.h"

void	init_heredoc(t_line *line, t_env *env, char *eof)
{
	char	*new_line;
	char	*heredoc_line;
	int		fd;
	int		save_in;
	
	new_line = NULL;
	heredoc_line = NULL;
	save_in = dup(0);
	close(0);
	fd = open(".heredoc", O_WRONLY | O_CREAT | O_TRUNC);
	while (get_line("heredoc> ", new_line, line, env))
	{
		if (ft_strcmp(new_line, eof) == 0)
			break ;
		heredoc_line = ft_strjoin_free(heredoc_line, new_line);
		heredoc_line = ft_strjoin_free(heredoc_line, "\n");
	}
//	execute_command(t_line *line);
	close(0);
	dup2(0, save_in);
}
