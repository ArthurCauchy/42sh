/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exc_mark_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumenthi <lumenthi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 16:54:02 by lumenthi          #+#    #+#             */
/*   Updated: 2018/11/08 11:30:00 by lumenthi         ###   ########.fr       */
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
#include "exc_mark.h"

char	*ft_add(char *before, char *middle, char *after)
{
	char	*ret;
	char	*tmp;

	tmp = ft_strjoin(before, middle);
	ret = ft_strjoin(tmp, after);
	free(tmp);
	return (ret);
}

int		is_backslash(char *str, int pos, int s_quote)
{
	int	ret;
	int	i;

	i = pos;
	while (str[i] && str[i - 1] == 92)
		i--;
	ret = pos - i;
	if (ret % 2 == 1 && !s_quote)
		return (1);
	return (0);
}

char	*exc_error(char *str)
{
	ft_putchar_fd('!', 2);
	ft_putstr_fd(str, 2);
	ft_putendl_fd(": event not found", 2);
	return (NULL);
}

int		check_matches(char *str1, char *str2)
{
	int i;

	i = 0;
	while (str1[i] && str2[i] && str1[i] == str2[i])
		i++;
	if (i == (int)ft_strlen(str1))
		return (i);
	else
		return (0);
}

int		is_legit(char *str, int pos)
{
	int	i;
	int	s_quote;
	int	d_quote;

	s_quote = 0;
	d_quote = 0;
	i = 0;
	while (i < pos && str[i])
	{
		if (str[i] == 34 && !is_backslash(str, i, 0))
			d_quote = (d_quote == 0) ? 1 : 0;
		else if (str[i] == 39 && !is_backslash(str, i, s_quote) && d_quote == 0)
			s_quote = (s_quote == 0) ? 1 : 0;
		i++;
	}
	if (s_quote == 1 || (pos - 1 > 0 && str[pos - 1] && str[pos - 1] == 92))
		return (0);
	return (1);
}
