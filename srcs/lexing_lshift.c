/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_lshift.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/04 14:15:05 by acauchy           #+#    #+#             */
/*   Updated: 2018/11/09 12:45:15 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lexing.h"

static void	lex_lshift_heredoc(char *cmdline,
		t_lexdata *lexdata, t_token *token)
{
	(void)cmdline;
	*token = LSHIFT2;
	++lexdata->i;
	lexdata->buff[lexdata->j++] = '<';
	lexdata->buff[lexdata->j++] = '<';
}

static void	lex_lshift_classic(char *cmdline,
		t_lexdata *lexdata, t_token *token)
{
	*token = LSHIFT;
	lexdata->buff[lexdata->j++] = '<';
	if (cmdline[lexdata->i + 1] == '&')
	{
		lexdata->buff[lexdata->j++] = '&';
		++lexdata->i;
		*token = LSHIFT_AMP;
	}
}

void		lex_lshift_word(char *cmdline, t_word **wordlist,
		t_lexdata *lexdata)
{
	t_token token;

	lex_shift_src_redirect(cmdline, wordlist, lexdata);
	if (cmdline[lexdata->i + 1] == '<')
		lex_lshift_heredoc(cmdline, lexdata, &token);
	else
		lex_lshift_classic(cmdline, lexdata, &token);
	lex_shift_dest_redirect(cmdline, wordlist, lexdata);
	lexdata->buff[lexdata->j] = '\0';
	lexdata->j = 0;
	add_word(token, lexdata->buff, wordlist, lexdata);
}
