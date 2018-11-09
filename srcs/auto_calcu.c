/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_calcu.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saxiao <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/17 17:38:07 by saxiao            #+#    #+#             */
/*   Updated: 2018/11/08 23:20:11 by saxiao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "line_edit.h"

void	init_win(t_autolist *list, int win_col, t_win *win)
{
	t_autolist	*cp;

	cp = list;
	win->ct_lt = 0;
	win->max = 0;
	while (cp)
	{
		if (cp->len > win->max)
			win->max = cp->len;
		cp = cp->next;
	}
	win->max++;
	cp = list;
	while (cp)
	{
		(win->ct_lt)++;
		cp = cp->next;
	}
	win->col = win_col / win->max;
	if (!win->col)
		win->col = 1;
	win->line = win->ct_lt / win->col;
	if (win->ct_lt % win->col > 0)
		win->line++;
}

int		nb_list(t_autolist *list)
{
	int		i;

	i = 0;
	while (list)
	{
		i++;
		list = list->next;
	}
	return (i);
}

void	free_auto_lt(t_line *line)
{
	t_autolist *temp;

	while (line->auto_lt)
	{
		temp = line->auto_lt;
		line->auto_lt = line->auto_lt->next;
		free(temp);
	}
}

void	is_tab(unsigned long key, t_line *line)
{
	if ((key == TAB_KEY && nb_list(line->auto_lt) > 1) || \
			(key_isarrow(key) && line->is_tabb4 == 1))
		line->is_tabb4 = 1;
	else
	{
		if (line->is_tabb4)
			clear_auto_onscreen(line);
		line->is_tabb4 = 0;
	}
}
