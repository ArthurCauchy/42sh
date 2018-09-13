/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_prompt_open_quote.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saxiao <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/27 15:52:52 by saxiao            #+#    #+#             */
/*   Updated: 2018/09/13 17:02:59 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edit.h"

static int		open_quote_exit(char *line)
{
	int		i;

	i = -1;
	g_open_squote = -1;
	g_open_dquote = -1;
	g_open_backslash = -1;
	while (line[++i])
	{
		if (line[i] == '"' && g_open_squote < 0 && dslash_before(line, i))
			g_open_dquote = -g_open_dquote;
		else if (line[i] == '\'' && g_open_dquote < 0 && \
				!(!dslash_before(line, i) && g_open_squote < 0))
			g_open_squote = -g_open_squote;
		else if (line[i] == '\\' && g_open_dquote < 0 && g_open_squote < 0 && \
				dslash_before(line, i) && !line[i + 1])
			g_open_backslash = -g_open_backslash;
	}
	if (g_open_dquote > 0 || g_open_squote > 0 || g_open_backslash > 0)
	{
		g_inside_doc_quote = 1;
		return (1);
	}
	g_inside_doc_quote = 0;
	return (0);
}

static void		for_open_quote(char *new_line, char *line, t_line *quote_line, char **env)
{
	if (!g_clc)
		ft_strcat(line, "\n");
	if (g_open_dquote > 0)
		get_line("dquote> ", new_line, quote_line, env);
	else
		get_line("quote> ", new_line, quote_line, env);
}

int				prompt_open_quote(char *line, char **env)
{
	char	new_line[INPUT_MAX_LEN];
	t_line	quote_line;

	while (open_quote_exit(line))
	{
		ft_bzero(new_line, INPUT_MAX_LEN);
		if (g_open_backslash > 0)
		{
			get_line("> ", new_line, &quote_line, env);
			line[ft_strlen(line) - 1] = '\0';
			ft_strcat(line, new_line);
			g_with_termcap ? ft_putchar('\n') : (void)g_with_termcap;
		}
		else
		{
			for_open_quote(new_line, line, &quote_line, env);
			if (ft_strlen(line) + ft_strlen(new_line) < INPUT_MAX_LEN - 1)
				ft_strcat(line, new_line);
			g_with_termcap ? ft_putchar('\n') : (void)g_with_termcap;
		}
		if (g_clc || g_dld)
			return (1);
	}
	return (0);
}
