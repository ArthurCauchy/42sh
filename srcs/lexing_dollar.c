/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/04 14:15:05 by acauchy           #+#    #+#             */
/*   Updated: 2018/11/09 12:21:01 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "utils.h"
#include "env.h"
#include "lexing.h"
#include "global.h"

static int	is_delim(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (0);
	return (1);
}

/*
** The purpose of this function is to inhibit the variables expansion when simple quoted.
** It simply copy the variable name as negated chars in the buffer, which is reverted later
** when variable substitution occurs.
*/

void		lex_dollar(char *cmdline, t_lexdata *lexdata)
{
	
	++lexdata->i;
	while (lexdata->j < INPUT_MAX_LEN - 2 && !is_delim(cmdline[lexdata->i]))
		lexdata->buff[lexdata->j++] = -cmdline[lexdata->i++];
	--lexdata->i;
}
