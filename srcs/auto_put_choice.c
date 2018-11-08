/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_put_choice.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saxiao <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 09:34:09 by saxiao            #+#    #+#             */
/*   Updated: 2018/11/08 23:41:06 by saxiao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edit.h"

static void	put_first_lst(t_line *line)
{
	char	dic[INPUT_MAX_LEN];
	char	*str;

	if (ft_strchr((char *)line->auto_compare, '/'))
	{
		path_last_slash((char *)line->auto_compare, dic, INPUT_MAX_LEN);
		str = line->auto_lt->name + ft_strlen((char *)line->auto_compare) - \
			ft_strlen(dic);
	}
	else
		str = line->auto_lt->name + ft_strlen((char *)line->auto_compare);
	while (*str)
	{
		if (*str == ' ' || *str == '\\')
			printable(line, '\\');
		printable(line, *str++);
	}
}

void		one_autolist(t_line *line)
{
	put_first_lst(line);
	move_nright(line);
	put_choice_end(line, line->auto_lt->is_dic);
	free_auto_lt(line);
}

static void	for_put_choice(t_autolist *cp, t_line *line)
{
	char		*str;

	str = cp->name;
	while (*str)
	{
		if (*str == ' ' || *str == '\\')
			printable(line, '\\');
		printable(line, *str++);
	}
	line->auto_is_dic = cp->is_dic;
}

void		put_choice(t_line *line, int *i)
{
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
				for_put_choice(cp, line);
			line->auto_last_choice_len = ft_strlen(cp->name);
		}
		cp = cp->next;
	}
	line->auto_ct = auto_ct_saver;
}
