/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_vars.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/04 14:15:05 by acauchy           #+#    #+#             */
/*   Updated: 2018/11/09 12:58:27 by acauchy          ###   ########.fr       */
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
	if (ft_isalnum(c) || c == '_')
		return (0);
	return (1);
}

static void	handle_special_varnames(char *src, int *i, char **var_value)
{
	if (src[*i] == '?')
		*var_value = ft_itoa(g_last_command_status);
	else if (src[*i] == '$')
		*var_value = ft_itoa(g_shell_pid);
	++(*i);
}

static void	write_variable(char *src, char *dest, int *i, int *j)
{
	char	var_name[4096];
	char	*var_value;
	size_t	k;

	var_value = NULL;
	++(*i);
	if (src[*i] == '?' || src[*i] == '$')
		handle_special_varnames(src, i, &var_value);
	else
	{
		k = 0;
		while (k < 4095 && !is_delim(src[*i]))
			var_name[k++] = src[(*i)++];
		var_name[k] = '\0';
		if (!(var_value = read_from_env(&g_env, var_name)))
			var_value = ft_strdup("");
	}
	--(*i);
	k = 0;
	while (k < ft_strlen(var_value) && *j < INPUT_MAX_LEN - 2)
		dest[(*j)++] = var_value[k++];
	free(var_value);
}

static void	var_subs_onword(t_word *word)
{
	int		i;
	int		j;
	char	new[INPUT_MAX_LEN];

	i = 0;
	j = 0;
	while (j < INPUT_MAX_LEN - 2 && word->str[i])
	{
		if (word->str[i] < 0)
			new[j++] = -word->str[i];
		else if (word->str[i] == '$')
			write_variable(word->str, new, &i, &j);
		else
			new[j++] = word->str[i];
		++i;
	}
	new[j] = '\0';
	free(word->str);
	word->str = ft_strdup(new);
}

void		apply_var_substitution(t_word *wordlist)
{
	t_word	*cur;

	cur = wordlist;
	while (cur)
	{
		if (cur->str)
			var_subs_onword(cur);
		cur = cur->next;
	}
}
