/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_start_current.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saxiao <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/17 15:39:00 by saxiao            #+#    #+#             */
/*   Updated: 2018/10/22 13:33:12 by saxiao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "line_edit.h"

static void	init_auto_start(int *i, int *find_start, int *res)
{
	*i = 0;
	*find_start = 0;
	*res = 0;
}

static void	for_auto_start(char *line, int *i, int *open_sq, int *open_dq)
{
	if (line[*i] == '"' && dslash_before(line, *i) && *open_sq < 0)
		*open_dq = -*open_dq;
	if (line[*i] == '\'' && dslash_before(line, *i) && *open_dq < 0)
		*open_sq = -*open_sq;
	(*i)++;
}

int			auto_start(char *line)
{
	int		i;
	int		find_start;
	int		res;
	int		open_squote;
	int		open_dquote;

	open_squote = -1;
	open_dquote = -1;
	init_auto_start(&i, &find_start, &res);
	while (!find_start)
	{
		res = i;
		while (line[i] && !(open_squote < 0 && open_dquote < 0 && \
					(line[i] == ' ' || line[i] == '\t')))
			for_auto_start(line, &i, &open_squote, &open_dquote);
		if (!line[i])
			find_start = 1;
		else
			i++;
	}
	return (res);
}

int			auto_current(t_line *line)
{
	int		i;

	i = auto_start((char *)line->buf);
	if (!i)
		return (0);
	i--;
	while (i > 0 && line->buf[i] == ' ')
		i--;
	if (line->buf[i] != ' ' && line->buf[i] != '&' && line->buf[i] != '|')
		return (1);
	return (0);
}
