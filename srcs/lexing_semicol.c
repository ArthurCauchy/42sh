/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_semicol.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/04 14:15:05 by acauchy           #+#    #+#             */
/*   Updated: 2018/08/23 11:33:13 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lexing.h"

void	lex_semicol_word(char *cmdline, t_word **wordlist,
		t_lexdata *lexdata)
{
	(void)cmdline;
	lexdata->buff[lexdata->j] = '\0';
	lexdata->j = 0;
	if (lexdata->force_add || ft_strlen(lexdata->buff) > 0)
		add_word(ARG, lexdata->buff, wordlist, lexdata);
	add_word(SEMICOL, ";", wordlist, lexdata);
}
