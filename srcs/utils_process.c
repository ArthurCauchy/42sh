/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/04 16:19:36 by acauchy           #+#    #+#             */
/*   Updated: 2018/11/06 11:15:18 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include "libft.h"

void	print_fatal_sig_name(int signo)
{
	if (signo == SIGHUP)
		ft_putendl_fd("Hangup", 2);
	else if (signo == SIGQUIT)
		ft_putendl_fd("Quit", 2);
	else if (signo == SIGILL)
		ft_putendl_fd("Illegal instruction", 2);
	else if (signo == SIGABRT)
		ft_putendl_fd("Aborted", 2);
	else if (signo == SIGFPE)
		ft_putendl_fd("Floating point exception", 2);
	else if (signo == SIGKILL)
		ft_putendl_fd("Killed", 2);
	else if (signo == SIGSEGV)
		ft_putendl_fd("Segmentation fault", 2);
	else if (signo == SIGALRM)
		ft_putendl_fd("Alarm clock", 2);
	else if (signo == SIGTERM)
		ft_putendl_fd("Terminated", 2);
	else if (signo == SIGUSR1)
		ft_putendl_fd("User defined signal 1", 2);
	else if (signo == SIGUSR2)
		ft_putendl_fd("User defined signal 2", 2);
}

int		get_process_return(int status)
{
	int	signo;

	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
	{
		signo = WTERMSIG(status);
		print_fatal_sig_name(signo);
		return (128 + signo);
	}
	else if (WIFSTOPPED(status))
	{
		signo = WSTOPSIG(status);
		ft_putendl_fd("Stopped", 2);
		return (128 + signo);
	}
	return (0);
}
