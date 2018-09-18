/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/18 15:59:23 by acauchy           #+#    #+#             */
/*   Updated: 2018/09/18 16:04:46 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "utils.h"
#include "line_edit.h"
#include "global.h"

char *ask_for_input(char *prompt)
{
	char    buffer[INPUT_MAX_LEN];
	t_line  line;

	ft_bzero(buffer, INPUT_MAX_LEN);
	get_line(prompt, buffer, &line, &g_env);
	if (g_with_termcap)
		ft_putchar('\n');
	return (ft_strdup(buffer));
}
