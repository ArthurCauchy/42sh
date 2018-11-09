/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_db.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/22 11:17:28 by acauchy           #+#    #+#             */
/*   Updated: 2018/11/09 16:58:54 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include "utils.h"

static int	heredoc_fds[MAX_HEREDOC_TMP];

void		init_heredoc_fds(void)
{
	ft_bzero(heredoc_fds, sizeof(int) * MAX_HEREDOC_TMP);
}

int			register_heredoc_fd(int fd)
{
	int	i;

	i = 0;
	while (i < MAX_HEREDOC_TMP && heredoc_fds[i])
		++i;
	if (i == MAX_HEREDOC_TMP)
		return (-1);
	heredoc_fds[i] = fd;
	return (0);
}

void		clear_heredocs_fds(void)
{
	int	i;

	i = 0;
	while (i < MAX_HEREDOC_TMP && heredoc_fds[i])
	{
		close(heredoc_fds[i]);
		heredoc_fds[i] = 0;
		++i;
	}
}
