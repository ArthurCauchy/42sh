/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_apply_lshift2.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 13:29:35 by acauchy           #+#    #+#             */
/*   Updated: 2018/06/25 14:57:49 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

int	apply_redirect_lshift2(t_redirect *redir,
		int *fdtmp_array, int *fdsave_array, char **errmsg)
{
	int	left_fd;
	int	heredoc_fd;

	left_fd = ft_atoi(redir->left);
	heredoc_fd = ft_atoi(redir->right);
	if (fdtmp_array && fdsave_array)
		save_filedes(fdtmp_array, fdsave_array, left_fd);
	if (left_fd != heredoc_fd)
	{
		if (dup2(heredoc_fd, left_fd) == -1)
			*errmsg = ft_strjoin("21sh: ", strerror(errno));
		close(heredoc_fd);
	}
	return (!*errmsg ? 0 : -1);
}
