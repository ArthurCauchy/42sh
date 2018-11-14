/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/18 15:59:23 by acauchy           #+#    #+#             */
/*   Updated: 2018/11/14 12:31:07 by saxiao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "../libft/libft.h"
#include "utils.h"
#include "line_edit.h"
#include "global.h"

static void		last_path(char *start, char *dic, int index)
{
	int		i;

	if (ft_strcmp(start, "/"))
	{
		i = ft_strlen(start) - 1;
		while (i >= 0 && start[i] != '/')
			i--;
		ft_bzero(dic, index);
		ft_strcpy(dic, start + i + 1);
	}
	else
		ft_strcpy(dic, start);
}

static void		get_normal_prompt(char *prompt, int index)
{
	char	pwd[INPUT_MAX_LEN];
	char	last_pwd[INPUT_MAX_LEN];
	char	*home;

	ft_bzero(prompt, index);
	ft_bzero(pwd, INPUT_MAX_LEN);
	getcwd(pwd, INPUT_MAX_LEN);
	home = read_from_env(&g_env, "HOME");
	if (home && ft_strcmp(pwd, home) == 0)
		ft_strcpy(last_pwd, "~");
	else
		last_path(pwd, last_pwd, INPUT_MAX_LEN);
	free(home);
	ft_strcpy(prompt, "-> ");
	ft_strcat(prompt, last_pwd);
	ft_strcat(prompt, " ");
}

static void		prompt_init(int prompt_choice, char *prompt, t_line *line)
{
	line->is_special_prompt = 1;
	ft_bzero(prompt, INPUT_MAX_LEN);
	if (prompt_choice == HEREDOC_PROMPT)
		ft_strcpy(prompt, "heredoc> ");
	else if (prompt_choice == DQUOTE_PROMPT)
		ft_strcpy(prompt, "dquote> ");
	else if (prompt_choice == SQUOTE_PROMPT)
		ft_strcpy(prompt, "squote> ");
	else if (prompt_choice == SLASH_PROMPT)
		ft_strcpy(prompt, "> ");
	else
	{
		line->is_special_prompt = 0;
		get_normal_prompt(prompt, INPUT_MAX_LEN);
	}
}

/*
** we can choose NORMAL_PROMPT, HEREDOC_PROMPT, SQUOTE_PROMPT,
** DQUOTE_PROMPT, SQUOTE_PROMPT
**
** If the input line is empty, returns :
** - an empty buffer if NORMAL_PROMPT
** - NULL if anything else
*/

char			*ask_for_input(int prompt_choice, char *ctrl)
{
	char	buffer[INPUT_MAX_LEN];
	char	prompt[INPUT_MAX_LEN];
	t_line	line;
	char	*ret;

	ft_bzero(buffer, INPUT_MAX_LEN);
	prompt_init(prompt_choice, prompt, &line);
	if (get_line(prompt, buffer, &line, &g_env) == 1
			&& prompt_choice != NORMAL_PROMPT)
		ret = NULL;
	else
		ret = ft_strdup(buffer);
	if (ctrl && line.clc)
		*ctrl = 'c';
	if (ctrl && line.dld)
		*ctrl = 'd';
	if (g_with_termcap)
		ft_putchar('\n');
	return (ret);
}
