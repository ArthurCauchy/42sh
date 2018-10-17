/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_auto_complet.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saxiao <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/17 15:05:59 by saxiao            #+#    #+#             */
/*   Updated: 2018/10/17 17:58:39 by saxiao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <curses.h>
#include <term.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include "../libft/ft_printf/includes/ft_printf.h"
#include "../headers/line_edit.h"

static void	put_first_lst(t_line *line)
{
	char	dic[INPUT_MAX_LEN];
	char	*str;

	if (ft_strchr((char *)line->auto_compare, '/'))
	{
		path_last_slash((char *)line->auto_compare, dic, INPUT_MAX_LEN);
		str = line->auto_lt->name + ft_strlen((char *)line->auto_compare) - ft_strlen(dic);
	}
	else
		str = line->auto_lt->name + ft_strlen((char *)line->auto_compare);
	while (*str)
		printable(line, *str++);
}

static void	one_autolist(t_line *line)
{
	put_first_lst(line);
	move_nright(line);
	put_choice_end(line, line->auto_lt->is_dic);
}

static void	put_choice(t_line *line, int *i)
{
	char		*str;
	t_autolist	*cp;
	int			auto_ct_saver;

	cp = line->auto_lt;
	auto_ct_saver = line->auto_ct;
	while (cp)
	{
		if (line->auto_ct % nb_list(line->auto_lt) == cp->ct)
		{
			if (line->auto_last_choice_len != -1)
			{
				*i = line->auto_last_choice_len + 1;
				while (--*i)
					delete_key(line);
			}
			if (line->auto_last_choice_len == -1)
				put_first_lst(line);
			else
			{
				str = cp->name;
				while (*str)
					printable(line, *str++);
			}
			line->auto_last_choice_len = ft_strlen(cp->name);
		}
		cp = cp->next;
	}
	line->auto_ct = auto_ct_saver;
}

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

int		my_tabkey(t_line *line, t_env **env)
{
	ft_bzero((char *)line->auto_compare, INPUT_MAX_LEN);
	ft_strcpy((char *)line->auto_compare, (char *)line->buf + auto_start((char *)line->buf));
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
		{
			init_attr(BASIC_LINE_EDIT);
			ft_printf("\n");
			init_attr(ADVANCED_LINE_EDIT);
			tputs(tgetstr("cd", 0), 1, my_putc);
			init_attr(BASIC_LINE_EDIT);
			put_colum(line);
			cusor_back(line);
			line->auto_ct = line->auto_ct + 1;;
		}
	}
	return (0);
}
