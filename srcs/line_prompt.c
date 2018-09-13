/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saxiao <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/27 17:15:49 by saxiao            #+#    #+#             */
/*   Updated: 2018/09/13 15:11:52 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "line_edit.h"

static void	init_add(t_history *add, char *new_line)
{
	ft_bzero(add->his, 0);
	ft_strcpy(add->his, new_line);
	add->next = NULL;
	add->pre = NULL;
}

static void	add_history(t_history **history, t_history *add)
{
	t_history	*temp;

	if (!*history)
		*history = add;
	else
	{
		temp = *history;
		(*history)->next = add;
		*history = add;
		(*history)->pre = temp;
	}
}

static int	not_empty(char *new_line)
{
	int		i;

	i = -1;
	while (new_line[++i])
	{
		if (new_line[i] != ' ' && new_line[i] != '\t')
			return (1);
	}
	return (0);
}

int			prompt(char **env)
{
	t_history			*add;
//	t_word				*list;

	ft_bzero(g_temp_file, MAX_BUF);
	ft_strcpy(g_temp_file, "./tmp_twentyone.c");
	while (42)
	{
		get_line("$> ", g_new_line, &g_line, env);
		g_with_termcap ? ft_putchar('\n') : (void)g_clc;
		if (not_empty(g_new_line))
		{
			add = malloc(sizeof(t_history));
			init_add(add, g_new_line);
			add_history(&g_history, add);
			prompt_open_quote(g_new_line, env);
			/*
			 actions for each line here
			if (!prompt_open_quote(g_new_line, env))
			{
				list = command_to_words(g_new_line);
				actions_each_line(&env, list, table);
				free_word_list(list);
			}
			*/
		}
	}
	return (0);
}
