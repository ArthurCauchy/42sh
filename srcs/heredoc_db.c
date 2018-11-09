/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_db.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/22 11:17:28 by acauchy           #+#    #+#             */
/*   Updated: 2018/06/22 16:02:05 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

int		register_heredoc_fd(int fd)
{
	int	i;

	i = 0;
	while (i < MAX_HEREDOC_TMP && g_shell.heredoc_fds[i])
		++i;
	if (i == MAX_HEREDOC_TMP)
		return (-1);
	g_shell.heredoc_fds[i] = fd;
	return (0);
}

void	clear_heredocs_fds(void)
{
	int	i;

	i = 0;
	while (i < MAX_HEREDOC_TMP && g_shell.heredoc_fds[i])
	{
		close(g_shell.heredoc_fds[i]);
		g_shell.heredoc_fds[i] = 0;
		++i;
	}
}
