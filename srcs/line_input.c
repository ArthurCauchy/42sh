/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/18 15:59:23 by acauchy           #+#    #+#             */
/*   Updated: 2018/10/18 14:34:07 by saxiao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../libft/libft.h"
#include "../headers/utils.h"
#include "../headers/line_edit.h"
#include "../headers/global.h"

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

//using getenv need to delect that func later on!!!!!!!
#include <stdlib.h>
static void		get_normal_prompt(char *prompt, int index)
{
	char	pwd[INPUT_MAX_LEN];
	char	last_pwd[INPUT_MAX_LEN];

	ft_bzero(prompt, index);
	ft_bzero(pwd, INPUT_MAX_LEN);
	getcwd(pwd, INPUT_MAX_LEN);
	if (!ft_strcmp(pwd, getenv("HOME")))
		ft_strcpy(last_pwd, "~");
	else
	last_path(pwd, last_pwd, INPUT_MAX_LEN);
	ft_strcpy(prompt, "-> ");
	ft_strcat(prompt, last_pwd);
	ft_strcat(prompt, " ");
}

// we can choose NORMAL_PROMPT, HEREDOC_PROMPT, SQUOTE_PROMPT, DQUOTE_PROMPT, SQUOTE_PROMPT
char *ask_for_input(int prompt_choice)
{
	char    buffer[INPUT_MAX_LEN];
	char    prompt[INPUT_MAX_LEN];
	t_line  line;

	ft_bzero(buffer, INPUT_MAX_LEN);
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
		get_normal_prompt(prompt, INPUT_MAX_LEN);
	get_line(prompt, buffer, &line, &g_env);
	if (g_with_termcap)
		ft_putchar('\n');
	return (ft_strdup(buffer));
}
