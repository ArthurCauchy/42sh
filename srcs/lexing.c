/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/02 13:53:13 by acauchy           #+#    #+#             */
/*   Updated: 2018/10/18 13:39:35 by saxiao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "utils.h"
#include "lexing.h"

#include "line_edit.h"
#include "global.h"

void			add_word(t_token token, char *str,
		t_word **wordlist, t_lexdata *lexdata)
{
	t_word	*word;
	t_word	*cur;

	word = new_word(token, str);
	if (!*wordlist)
		*wordlist = word;
	else
	{
		cur = *wordlist;
		while (cur->next)
			cur = cur->next;
		cur->next = word;
	}
	lexdata->force_add = 0;
}

static void		update_quotes(char *cmdline, t_lexdata *lexdata)
{
	lexdata->force_add = 1;
	if (lexdata->quoted == 0)
	{
		if (cmdline[lexdata->i] == '\'')
			lexdata->quoted = 1;
		else if (cmdline[lexdata->i] == '"')
			lexdata->quoted = 2;
	}
	else if (lexdata->quoted == 1)
	{
		if (cmdline[lexdata->i] == '\'')
			lexdata->quoted = 0;
		else if (cmdline[lexdata->i] == '"')
			lexdata->buff[lexdata->j++] = cmdline[lexdata->i];
	}
	else if (lexdata->quoted == 2)
	{
		if (cmdline[lexdata->i] == '"')
			lexdata->quoted = 0;
		else if (cmdline[lexdata->i] == '\'')
			lexdata->buff[lexdata->j++] = cmdline[lexdata->i];
	}
}

static void		init_lexdata(t_lexdata **lexdata)
{
	if (!(*lexdata = (t_lexdata*)ft_memalloc(sizeof(t_lexdata))))
		exit_error("ft_memalloc() error");
	if (!((*lexdata)->buff = (char*)malloc(INPUT_MAX_LEN)))
		exit_error("malloc() error");
}

static void		do_lex(char *cmdline, t_word **wordlist,
		t_lexdata *lexdata, char **errmsg)
{
	if (!lexdata->quoted && is_separator(cmdline[lexdata->i]))
		lex_space_word(cmdline, wordlist, lexdata, errmsg);
	else if (!lexdata->quoted && cmdline[lexdata->i] == ';')
		lex_semicol_word(cmdline, wordlist, lexdata, errmsg);
	else if (!lexdata->quoted && cmdline[lexdata->i] == '|')
		lex_pipe_or_word(cmdline, wordlist, lexdata, errmsg);
	else if (!lexdata->quoted && cmdline[lexdata->i] == '&')
		lex_amp_and_word(cmdline, wordlist, lexdata, errmsg);
	else if (!lexdata->quoted && cmdline[lexdata->i] == '>')
		lex_rshift_word(cmdline, wordlist, lexdata, errmsg);
	else if (!lexdata->quoted && cmdline[lexdata->i] == '<')
		lex_lshift_word(cmdline, wordlist, lexdata, errmsg);
	else if (!lexdata->quoted && cmdline[lexdata->i] == '~'
			&& lexdata->j == 0)
		lex_tilde_exp(cmdline, lexdata, errmsg);
	else if (lexdata->quoted != 1 && cmdline[lexdata->i] == '\\')
		lex_escape(cmdline, lexdata, errmsg);
	else if (lexdata->quoted != 1 && cmdline[lexdata->i] == '$')
		lex_dollar_exp(cmdline, lexdata, errmsg);
	else if (cmdline[lexdata->i] == '\'' || cmdline[lexdata->i] == '"')
		update_quotes(cmdline, lexdata);
	else
		lexdata->buff[lexdata->j++] = cmdline[lexdata->i];
}

void			lex_analysis(char **cmdline, t_word **wordlist, char **errmsg)
{
	t_lexdata	*lexdata;

	init_lexdata(&lexdata);
	while (42)
	{
		do_lex(*cmdline, wordlist, lexdata, errmsg);
		if (*errmsg)
			break ;
		++lexdata->i;
		if (lexdata->i > ft_strlen(*cmdline))
		{
			if (lexdata->quoted != 0 || lexdata->escaped == 1)
			{
				free(lexdata->buff);
				free(lexdata);
				delete_wordlist(wordlist);
				*cmdline = ft_strjoin_free(*cmdline, ask_for_input(SLASH_PROMPT));
				init_lexdata(&lexdata);
				// check command too long here
			}
			else
				break;
		}
	}
	free(lexdata->buff);
	free(lexdata);
}
