/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/20 12:03:19 by acauchy           #+#    #+#             */
/*   Updated: 2018/11/09 11:56:49 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "libft.h"

void	exit_error(char *errmsg)
{
	if (errmsg)
		ft_putendl_fd(errmsg, 2);
	else
		ft_putendl_fd("error", 2);
	exit(1);
}

int		is_there_a_file(char *filepath)
{
	if (access(filepath, F_OK) == 0)
		return (1);
	return (0);
}

int		is_executable(char *filepath)
{
	struct stat	fileinfo;

	if (access(filepath, X_OK) == 0
			&& stat(filepath, &fileinfo) != -1
			&& S_ISREG(fileinfo.st_mode))
		return (1);
	return (0);
}

int		is_directory(char *filepath)
{
	struct stat	fileinfo;

	if (access(filepath, X_OK) == 0
			&& stat(filepath, &fileinfo) != -1
			&& S_ISDIR(fileinfo.st_mode))
		return (1);
	return (0);
}

int		is_separator(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\0');
}
