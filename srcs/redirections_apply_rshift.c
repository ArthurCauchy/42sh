/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_apply_rshift.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 13:29:29 by acauchy           #+#    #+#             */
/*   Updated: 2018/06/25 14:52:11 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <errno.h>
#include "libft.h"
#include "redirects.h"

int	apply_redirect_rshift(t_redirect *redir,
		int *fdtmp_array, int *fdsave_array, char **errmsg)
{
	int	left_fd;
	int	file_fd;

	if (ft_strlen(redir->left) > 0)
		left_fd = ft_atoi(redir->left);
	else
		left_fd = 1;
	file_fd = open_file_fd(redir->right, 1, 0, errmsg);
	if (file_fd < 0)
		return (-1);
	if (fdtmp_array && fdsave_array)
		save_filedes(fdtmp_array, fdsave_array, left_fd);
	if (file_fd != left_fd)
	{
		if (dup2(file_fd, left_fd) == -1)
			*errmsg = ft_strjoin("42sh: ", strerror(errno));
		close(file_fd);
	}
	return (!*errmsg ? 0 : -1);
}
