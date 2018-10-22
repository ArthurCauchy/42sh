/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_auto_complet.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saxiao <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/17 15:05:59 by saxiao            #+#    #+#             */
/*   Updated: 2018/10/22 20:23:38 by saxiao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <curses.h>
#include <term.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include "ft_printf.h"
#include "line_edit.h"
#include "global.h"

static void	cusor_back(t_line *line)
{
	int		i;

	i = line->w.line + 2;
	init_attr(ADVANCED_LINE_EDIT);
	while (--i)
		tputs(tgetstr("up", 0), 1, my_putc);
	line->pos = 0 - line->start_po;
	move_nright(line);
	put_choice(line, &i);
}

static void	print_autolist(t_line *line)
{
	init_attr(BASIC_LINE_EDIT);
	ft_printf("\n");
	init_attr(ADVANCED_LINE_EDIT);
	tputs(tgetstr("cd", 0), 1, my_putc);
	init_attr(BASIC_LINE_EDIT);
	put_colum(line);
	cusor_back(line);
	line->auto_ct = line->auto_ct + 1;
}

static void	home_auto_compare(t_line *line)
{
	char	*user_home;
	char	temp[INPUT_MAX_LEN];

	user_home = NULL;
	ft_bzero(temp, INPUT_MAX_LEN);
	if (line->auto_compare[0] == '~')
	{
		user_home = read_from_env(&g_env, "HOME");
		if (user_home)
		{
		ft_strcpy((char *)temp, user_home);
		ft_strcat(temp, (char *)line->auto_compare + 1);
		ft_bzero(line->auto_compare, INPUT_MAX_LEN);
		ft_strcpy((char *)line->auto_compare, (char *)temp);
		free(user_home);
		}
	}
}

int			my_tabkey(t_line *line, t_env **env)
{
	ft_bzero((char *)line->auto_compare, INPUT_MAX_LEN);
	ft_strcpy((char *)line->auto_compare, (char *)line->buf + \
			auto_start((char *)line->buf));
	home_auto_compare(line);
	if (line->auto_ct == -1)
	{
		free_auto_lt(line);
		line->auto_lt = get_autolist(line, env);
		init_win(line->auto_lt, line->line_max, &(line->w));
		sort_list(&line->auto_lt);
	}
	if (nb_list(line->auto_lt))
	{
		if (nb_list(line->auto_lt) == 1)
			one_autolist(line);
		else
			print_autolist(line);
	}
	return (0);
}
