/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_shift.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/13 11:59:57 by acauchy           #+#    #+#             */
/*   Updated: 2018/08/23 11:34:18 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lexing.h"

void	lex_shift_src_redirect(char *cmdline, t_word **wordlist,
		t_lexdata *lexdata)
{
	char	src_fd;

	(void)cmdline;
	src_fd = 0;
	if (lexdata->j == 1 && ft_isdigit(src_fd = lexdata->buff[lexdata->j - 1]))
		--lexdata->j;
	lexdata->buff[lexdata->j] = '\0';
	lexdata->j = 0;
	if (lexdata->force_add || ft_strlen(lexdata->buff) > 0)
		add_word(ARG, lexdata->buff, wordlist, lexdata);
	if (ft_isdigit(src_fd))
		lexdata->buff[lexdata->j++] = src_fd;
}

void	lex_shift_dest_redirect(char *cmdline, t_word **wordlist,
		t_lexdata *lexdata)
{
	(void)wordlist;
	if (cmdline[lexdata->i + 1] == '&')
	{
		lexdata->buff[lexdata->j++] = '&';
		++lexdata->i;
	}
}
