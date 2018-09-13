/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_cp_cut.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saxiao <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/27 15:43:11 by saxiao            #+#    #+#             */
/*   Updated: 2018/09/13 17:00:05 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edit.h"

int		cp_all(t_line *line)
{
	ft_bzero(line->cp, INPUT_MAX_LEN);
	ft_strcpy((char *)line->cp, (char *)line->buf);
	return (0);
}

int		cp_begin(t_line *line)
{
	int		i;

	i = line->pos;
	ft_bzero(line->cp, INPUT_MAX_LEN);
	ft_strncpy((char *)line->cp, (char *)line->buf, i);
	return (0);
}

int		cp_end(t_line *line)
{
	int		i;

	i = line->buf_len - line->pos;
	ft_bzero(line->cp, INPUT_MAX_LEN);
	ft_strncpy((char *)line->cp, (char *)line->buf + line->pos, i);
	return (0);
}

int		cut_all(t_line *line)
{
	cp_all(line);
	delete_all(line);
	return (0);
}

int		cut_begin(t_line *line)
{
	cp_begin(line);
	while (line->pos)
		delete_key(line);
	return (0);
}
