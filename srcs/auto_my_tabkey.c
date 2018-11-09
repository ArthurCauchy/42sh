/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_auto_complet.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saxiao <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/17 15:05:59 by saxiao            #+#    #+#             */
/*   Updated: 2018/11/08 23:43:52 by saxiao           ###   ########.fr       */
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

int			nb_line_command(t_line *line)
{
	int		i;
	int		j;
	int		res;
	char	all[INPUT_MAX_LEN + line->start_po];

	ft_bzero(all, INPUT_MAX_LEN + line->start_po);
	ft_strcpy(all, (char *)line->prompt);
	ft_strcat(all, (char *)line->buf);
	j = 0;
	res = 0;
	i = 0;
	while (i < line->start_po + line->buf_len)
	{
		if ((i - j) % line->line_max == 0 || all[i] == '\n')
		{
			res++;
			j = i;
		}
		i++;
	}
	return (res);
}

void		cusor_back(t_line *line)
{
	int		i;

	i = line->real_nb_auto_line + nb_line_command(line) + 1;
	init_attr(ADVANCED_LINE_EDIT);
	tputs(tgetstr("cr", 0), 1, my_putc);
	while (--i > 1)
		tputs(tgetstr("up", 0), 1, my_putc);
	i = line->start_po + 1;
	while (--i)
		tputs(tgetstr("nd", 0), 1, my_putc);
	line->pos = 0;
	move_nright(line);
}

static void	print_autolist(t_line *line)
{
	int		i;

	i = 0;
	put_choice(line, &i);
	init_attr(BASIC_LINE_EDIT);
	if (last_letter_not_last_col(line))
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
