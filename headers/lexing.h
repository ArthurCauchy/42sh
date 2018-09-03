/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 14:20:15 by acauchy           #+#    #+#             */
/*   Updated: 2018/08/23 11:11:39 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __LEXING_H
# define __LEXING_H

typedef enum		e_token
{
	ARG,
	LSHIFT,
	LSHIFT_AMP,
	LSHIFT2,
	RSHIFT,
	RSHIFT_AMP,
	RSHIFT2,
	PIPE,
	FDCLOSE,
	AND,
	OR,
	SEMICOL,
	AMP
}					t_token;

typedef struct		s_lexdata
{
	char		*buff;
	size_t	i;
	size_t	j;
	int			quoted;
	int			force_add;
}					t_lexdata;

typedef struct		s_word
{
	t_token			token;
	char			*str;
	struct s_word	*next;
}					t_word;

/*
** word.c
*/

t_word	*new_word(t_token token, char *str);
void	remove_word(t_word **wordlist, t_word *word);
void	delete_wordlist(t_word **head);

/*
** lexing.c, lexing_[token].c
*/

void	add_word(t_token token, char *str,
		t_word **wordlist, t_lexdata *lexdata);
void	lex_analysis(char *cmdline, t_word **wordlist, char **errmsg);
void	lex_semicol_word(char *cmdline, t_word **wordlist, t_lexdata *lexdata,
		char **errmsg);
void	lex_space_word(char *cmdline, t_word **wordlist, t_lexdata *lexdata,
		char **errmsg);
void	lex_amp_and_word(char *cmdline, t_word **wordlist, t_lexdata *lexdata,
		char **errmsg);
void	lex_pipe_or_word(char *cmdline, t_word **wordlist, t_lexdata *lexdata,
		char **errmsg);
void	lex_shift_src_redirect(char *cmdline, t_word **wordlist, t_lexdata *lexdata,
		char **errmsg);
void	lex_shift_dest_redirect(char *cmdline, t_word **wordlist, t_lexdata *lexdata,
		char **errmsg);
void	lex_rshift_word(char *cmdline, t_word **wordlist, t_lexdata *lexdata,
		char **errmsg);
void	lex_lshift_word(char *cmdline, t_word **wordlist, t_lexdata *lexdata,
		char **errmsg);
void	lex_tilde_exp(char *cmdline, t_lexdata *lexdata, char **errmsg);
void	lex_dollar_exp(char *cmdline, t_lexdata *lexdata, char **errmsg);

#endif
