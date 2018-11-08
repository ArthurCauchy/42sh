/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_amp_and.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/04 14:15:05 by acauchy           #+#    #+#             */
/*   Updated: 2018/11/08 14:27:01 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lexing.h"

void	lex_amp_and_word(char *cmdline, t_word **wordlist,
		t_lexdata *lexdata)
{
	lexdata->buff[lexdata->j] = '\0';
	lexdata->j = 0;
	if (lexdata->force_add || ft_strlen(lexdata->buff) > 0)
		add_word(ARG, lexdata->buff, wordlist, lexdata);
	if (cmdline[lexdata->i + 1] == '&')
	{
		add_word(AND, "&&", wordlist, lexdata);
		++lexdata->i;
	}
	else
		add_word(ARG, "&", wordlist, lexdata);
}
