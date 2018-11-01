/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_rshift.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/04 14:15:05 by acauchy           #+#    #+#             */
/*   Updated: 2018/08/23 11:34:40 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lexing.h"

static void	lex_rshift_append(char *cmdline, t_lexdata *lexdata, t_token *token)
{
	(void)cmdline;
	*token = RSHIFT2;
	++lexdata->i;
	lexdata->buff[lexdata->j++] = '>';
	lexdata->buff[lexdata->j++] = '>';
}

static void	lex_rshift_classic(char *cmdline,
		t_lexdata *lexdata, t_token *token)
{
	*token = RSHIFT;
	lexdata->buff[lexdata->j++] = '>';
	if (cmdline[lexdata->i + 1] == '&')
	{
		lexdata->buff[lexdata->j++] = '&';
		++lexdata->i;
		*token = RSHIFT_AMP;
	}
}

void		lex_rshift_word(char *cmdline, t_word **wordlist,
		t_lexdata *lexdata)
{
	t_token token;

	lex_shift_src_redirect(cmdline, wordlist, lexdata);
	if (cmdline[lexdata->i + 1] == '>')
		lex_rshift_append(cmdline, lexdata, &token);
	else
		lex_rshift_classic(cmdline, lexdata, &token);
	lex_shift_dest_redirect(cmdline, wordlist, lexdata);
	lexdata->buff[lexdata->j] = '\0';
	lexdata->j = 0;
	add_word(token, lexdata->buff, wordlist, lexdata);
}
