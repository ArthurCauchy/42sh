/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_space.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/04 14:15:05 by acauchy           #+#    #+#             */
/*   Updated: 2018/08/23 11:35:08 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "utils.h"
#include "lexing.h"

void	lex_space_word(char *cmdline, t_word **wordlist,
		t_lexdata *lexdata)
{
	lexdata->buff[lexdata->j] = '\0';
	lexdata->j = 0;
	if (lexdata->force_add || ft_strlen(lexdata->buff) > 0)
		add_word(ARG, lexdata->buff, wordlist, lexdata);
	while (lexdata->i <= ft_strlen(cmdline)
			&& is_separator(cmdline[lexdata->i]))
		++lexdata->i;
	--lexdata->i;
}
