/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_tilde.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/04 14:15:05 by acauchy           #+#    #+#             */
/*   Updated: 2018/11/09 12:50:49 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "lexing.h"
#include "global.h"

void	lex_tilde_exp(char *cmdline, t_lexdata *lexdata)
{
	char	*home;
	size_t	i;

	(void)cmdline;
	if (!(home = read_from_env(&g_env, "HOME")))
		return ;
	i = 0;
	while (i < ft_strlen(home))
		lexdata->buff[lexdata->j++] = -home[i++];
	free(home);
}
