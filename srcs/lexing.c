/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/02 13:53:13 by acauchy           #+#    #+#             */
/*   Updated: 2018/11/09 14:17:23 by acauchy          ###   ########.fr       */
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
	t_word	**target;
	char	*alias;

	target = wordlist;
	while (*target)
		target = &((*target)->next);
	if ((!lexdata->avoid || ft_strcmp(str, lexdata->avoid)) != 0
			&& (*target == NULL || (*target)->token == PIPE
				|| (*target)->token == AND || (*target)->token == OR
				|| (*target)->token == SEMICOL)
			&& !(lexdata->force_add) && (alias = get_alias_value(str)))
	{
		lex_analysis(&alias, wordlist, str);
	}
	else
		*target = new_word(token, str);
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
			lexdata->buff[lexdata->j++] = -cmdline[lexdata->i];
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
		t_lexdata *lexdata)
{
	if (!lexdata->quoted && is_separator(cmdline[lexdata->i]))
		lex_space_word(cmdline, wordlist, lexdata);
	else if (!lexdata->quoted && cmdline[lexdata->i] == ';')
		lex_semicol_word(cmdline, wordlist, lexdata);
	else if (!lexdata->quoted && cmdline[lexdata->i] == '|')
		lex_pipe_or_word(cmdline, wordlist, lexdata);
	else if (!lexdata->quoted && cmdline[lexdata->i] == '&')
		lex_amp_and_word(cmdline, wordlist, lexdata);
	else if (!lexdata->quoted && cmdline[lexdata->i] == '>')
		lex_rshift_word(cmdline, wordlist, lexdata);
	else if (!lexdata->quoted && cmdline[lexdata->i] == '<')
		lex_lshift_word(cmdline, wordlist, lexdata);
	else if (!lexdata->quoted && cmdline[lexdata->i] == '~'
			&& lexdata->j == 0)
		lex_tilde_exp(cmdline, lexdata);
	else if (lexdata->quoted != 1 && cmdline[lexdata->i] == '\\')
		lex_escape(cmdline, lexdata);
	else if (cmdline[lexdata->i] == '\'' || cmdline[lexdata->i] == '"')
		update_quotes(cmdline, lexdata);
	else if (lexdata->quoted == 1)
		lexdata->buff[lexdata->j++] = -cmdline[lexdata->i];
	else
		lexdata->buff[lexdata->j++] = cmdline[lexdata->i];
}

/*
** Params:
** - cmdline : the input buffer
** - wordlist : the output list containing the lexed tokens
** - avoid : the name of the alias to ignore in cas of alias lexing, or NULL
**
** Returns:
** - 0 : OK
** - 1 : non closed single quotes
** - 2 : non closed double quotes
** - 3 : line ended with backslash
*/

int				lex_analysis(char **cmdline, t_word **wordlist, char *avoid)
{
	t_lexdata	*lexdata;
	int			ret;

	init_lexdata(&lexdata);
	lexdata->avoid = avoid;
	ret = 0;
	while (42)
	{
		do_lex(*cmdline, wordlist, lexdata);
		++lexdata->i;
		if (lexdata->i > ft_strlen(*cmdline))
		{
			if (!avoid && lexdata->escaped == 1)
				ret = 3;
			else if (!avoid && lexdata->quoted != 0)
				ret = lexdata->quoted;
			break ;
		}
	}
	free(lexdata->buff);
	free(lexdata);
	return (ret);
}
