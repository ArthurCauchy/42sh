/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/04 14:15:05 by acauchy           #+#    #+#             */
/*   Updated: 2018/10/19 14:35:08 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "utils.h"
#include "env.h"
#include "lexing.h"
#include "global.h"

static int	is_delim(char c)
{
	if (is_separator(c)
			|| c == '/'
			|| c == ';'
			|| c == '|'
			|| c == '>'
			|| c == '<'
			|| c == '~'
			|| c == '$'
			|| c == '\''
			|| c == '"')
		return (1);
	return (0);
}

static void	handle_special_varnames(char *cmdline,
		t_lexdata *lexdata, char **var_value)
{
	if (cmdline[lexdata->i] == '?')
		*var_value = ft_itoa(g_last_command_status);
	++lexdata->i;
}

void		lex_dollar_exp(char *cmdline, t_lexdata *lexdata, char **errmsg)
{
	char	var_name[4096];
	char	*var_value;
	size_t	i;

	var_value = NULL;
	++lexdata->i;
	if (cmdline[lexdata->i] == '?')
		handle_special_varnames(cmdline, lexdata, &var_value);
	else
	{
		i = 0;
		while (i < 4095 && !is_delim(cmdline[lexdata->i]))
			var_name[i++] = cmdline[lexdata->i++];
		var_name[i] = '\0';
		if (!(var_value = read_from_env(&g_env, var_name)))
		{
			*errmsg = ft_strjoin(var_name, ": Undefined variable.");
			return ;
		}
	}
	--lexdata->i;
	i = 0;
	while (i < ft_strlen(var_value))
		lexdata->buff[lexdata->j++] = var_value[i++];
	free(var_value);
}
