/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saxiao <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/22 12:09:44 by saxiao            #+#    #+#             */
/*   Updated: 2018/11/06 11:23:26 by saxiao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <stdlib.h>
#include "env.h"
#include "global.h"
#include "line_edit.h"

int				dslash_before(char *line, int index)
{
	int		i;
	int		j;

	i = 0;
	j = index - 1;
	while (j >= 0 && line[j] == '\\')
	{
		i++;
		j--;
	}
	if (!(i % 2))
		return (1);
	return (0);
}

unsigned long	get_key(void)
{
	unsigned char	buff[6];

	ft_bzero(buff, 6);
	read(0, buff, 6);
	return (buff[0] + (buff[1] << 8) + (buff[2] << 16) + (buff[3] << 24) + \
			((unsigned long)buff[4] << 32) + ((unsigned long)buff[5] << 40));
}

char			**path(t_env **env)
{
	char	*path;
	char	**split_path;

	if (!(path = read_from_env(env, "PATH")))
		return (NULL);
	split_path = ft_strsplit(path, ':');
	free(path);
	return (split_path);
}

int				my_putc(int c)
{
	write(1, &c, 1);
	return (0);
}
