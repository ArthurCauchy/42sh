/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumenthi <lumenthi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 14:56:06 by lumenthi          #+#    #+#             */
/*   Updated: 2018/11/07 20:32:55 by lumenthi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include "utils.h"
#include "global.h"
#include "history.h"

char		*to_string(char **ar)
{
	char	*line;
	int		i;

	i = 0;
	line = ft_strdup("");
	while (ar[i])
	{
		line = ft_strjoinl(line, ar[i]);
		line = ft_strjoinl(line, "\n");
		i++;
	}
	return (line);
}

char		*read_file(int fd)
{
	char	*line;
	char	buf[2];
	int		ret;

	line = ft_strdup("");
	while ((ret = read(fd, buf, 1)))
	{
		buf[ret] = '\0';
		line = ft_strjoinl(line, buf);
	}
	return (line);
}

int			get_elems(char *line)
{
	int		count;
	int		i;

	count = 0;
	i = 0;
	while (line[i])
	{
		if (line[i++] == '\n')
			count++;
	}
	return (count);
}

void		hist_null(char ***hist)
{
	int i;

	i = 0;
	while (i <= g_history->size)
	{
		(*hist)[i] = NULL;
		i++;
	}
}
