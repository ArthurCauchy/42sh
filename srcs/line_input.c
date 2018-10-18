/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/18 15:59:23 by acauchy           #+#    #+#             */
/*   Updated: 2018/10/18 12:39:54 by saxiao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../libft/libft.h"
#include "../headers/utils.h"
#include "../headers/line_edit.h"
#include "../headers/global.h"

static void	get_normal_prompt(char *prompt, int index)
{
	char	pwd[INPUT_MAX_LEN];
	char	last_pwd[INPUT_MAX_LEN];

	ft_bzero(prompt, index);
	ft_bzero(pwd, INPUT_MAX_LEN);
	getcwd(pwd, INPUT_MAX_LEN);
	path_last_slash(pwd, last_pwd, INPUT_MAX_LEN);
}

char *ask_for_input(int prompt_choice)
{
	char    buffer[INPUT_MAX_LEN];
	t_line  line;

	ft_bzero(buffer, INPUT_MAX_LEN);
	get_line(prompt, buffer, &line, &g_env);
	if (g_with_termcap)
		ft_putchar('\n');
	return (ft_strdup(buffer));
}
