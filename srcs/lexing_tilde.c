/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_tilde.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/04 14:15:05 by acauchy           #+#    #+#             */
/*   Updated: 2018/08/23 11:32:37 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "lexing.h"
#include "global.h"

void	lex_tilde_exp(char *cmdline, t_lexdata *lexdata, char **errmsg)
{
	char	*home;
	size_t	i;

	(void)cmdline;
	if (!(home = read_from_env(&g_env, "HOME")))
	{
		*errmsg = ft_strdup("No $HOME variable set.");
		return ;
	}
	i = 0;
	while (i < ft_strlen(home))
		lexdata->buff[lexdata->j++] = home[i++];
	free(home);
}
