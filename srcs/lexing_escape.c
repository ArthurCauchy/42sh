/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_escape.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/04 14:15:05 by acauchy           #+#    #+#             */
/*   Updated: 2018/11/09 14:48:43 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "lexing.h"

void	lex_escape(char *cmdline, t_lexdata *lexdata)
{
	char	next_char;

	lexdata->force_add = 1;
	next_char = cmdline[lexdata->i + 1];
	if (next_char)
	{
		if (lexdata->quoted == 2 && next_char != '"'
				&& next_char != '\\' && next_char != '$')
			lexdata->buff[lexdata->j++] = '\\';
		lexdata->buff[lexdata->j++] = -next_char;
		++lexdata->i;
	}
	else
	{
		lexdata->escaped = 1;
		cmdline[lexdata->i] = '\0';
	}
}
