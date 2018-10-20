/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_apply_lshift.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 13:29:17 by acauchy           #+#    #+#             */
/*   Updated: 2018/06/25 14:50:53 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

int	apply_redirect_lshift(t_redirect *redir,
		int *fdtmp_array, int *fdsave_array, char **errmsg)
{
	int	left_fd;
	int	file_fd;

	left_fd = ft_atoi(redir->left);
	file_fd = open_file_fd(redir->right, 0, 0, errmsg);
	if (file_fd < 0)
		return (-1);
	if (fdtmp_array && fdsave_array)
		save_filedes(fdtmp_array, fdsave_array, left_fd);
	if (file_fd != left_fd)
	{
		if (dup2(file_fd, left_fd) == -1)
			*errmsg = ft_strjoin("21sh: ", strerror(errno));
		close(file_fd);
	}
	return (!*errmsg ? 0 : -1);
}
