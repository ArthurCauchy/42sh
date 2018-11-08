/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_escape.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/04 14:15:05 by acauchy           #+#    #+#             */
/*   Updated: 2018/11/08 23:38:50 by arthur           ###   ########.fr       */
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
		if (lexdata->quoted == 2 && next_char != '"')
			lexdata->buff[lexdata->j++] = '\\';
		lexdata->buff[lexdata->j++] = cmdline[lexdata->i + 1];
		++lexdata->i;
	}
	else
	{
		lexdata->escaped = 1;
		cmdline[lexdata->i] = '\0';
	}
}
