/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_apply.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 13:29:12 by acauchy           #+#    #+#             */
/*   Updated: 2018/11/09 14:06:23 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include "libft.h"
#include "redirects.h"

/*
** mode :
** 0) read
** 1) write
*/

int			open_file_fd(char *filename, int mode, int append, char **errmsg)
{
	int flags;
	int fd;

	if (mode == 0)
		flags = O_RDONLY;
	else
	{
		flags = O_WRONLY | O_CREAT;
		if (append == 1)
			flags = flags | O_APPEND;
		else
			flags = flags | O_TRUNC;
	}
	fd = open(filename, flags, 0644);
	if (fd < 0)
	{
		*errmsg = ft_strdup(filename);
		*errmsg = ft_strjoin_free(*errmsg, ft_strdup(": "));
		*errmsg = ft_strjoin_free(*errmsg, ft_strdup(strerror(errno)));
	}
	return (fd);
}

static int	apply_redirect(t_redirect *redir, int *fdtmp_array,
		int *fdsave_array, char **errmsg)
{
	if (redir->token == PIPE)
		return (apply_redirect_pipe(redir, fdtmp_array, fdsave_array, errmsg));
	if (redir->token == FDCLOSE)
		return (close(ft_atoi(redir->right)) * 0);
	else if (redir->token == LSHIFT)
		return (apply_redirect_lshift(redir,
				fdtmp_array, fdsave_array, errmsg));
	else if (redir->token == LSHIFT_AMP)
		return (apply_redirect_lshift_amp(redir,
				fdtmp_array, fdsave_array, errmsg));
	else if (redir->token == LSHIFT2)
		return (apply_redirect_lshift2(redir,
				fdtmp_array, fdsave_array, errmsg));
	else if (redir->token == RSHIFT)
		return (apply_redirect_rshift(redir,
				fdtmp_array, fdsave_array, errmsg));
	else if (redir->token == RSHIFT_AMP)
		return (apply_redirect_rshift_amp(redir,
				fdtmp_array, fdsave_array, errmsg));
	else if (redir->token == RSHIFT2)
		return (apply_redirect_rshift2(redir,
				fdtmp_array, fdsave_array, errmsg));
	else
		return (0);
}

int			apply_redirects(t_redirect *redirs, int *fdtmp_array,
		int *fdsave_array, char **errmsg)
{
	t_redirect	*cur;
	int			ret;

	cur = redirs;
	while (cur)
	{
		ret = apply_redirect(cur, fdtmp_array, fdsave_array, errmsg);
		if (ret == -1)
			return (-1);
		cur = cur->next;
	}
	return (0);
}
