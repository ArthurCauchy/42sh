/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumenthi <lumenthi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 14:13:44 by lumenthi          #+#    #+#             */
/*   Updated: 2018/11/07 10:42:47 by lumenthi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "libft.h"
#include <stdlib.h>

t_error		init_error(void)
{
	t_error ret;

	ret.before = 0;
	ret.after = 0;
	ret.separator = NONE;
	ret.msg = NULL;
	return (ret);
}

static int	parse_error(t_token token)
{
	ft_putstr_fd("Parse error near token `", 2);
	if (token == PIPE)
		ft_putstr_fd("|", 2);
	else if (token == OR)
		ft_putstr_fd("||", 2);
	else if (token == AND)
		ft_putstr_fd("&&", 2);
	else if (token == SEMICOL)
		ft_putstr_fd(";", 2);
	ft_putstr_fd("'\n", 2);
	return (0);
}

static int	no_error(t_word **tmp, t_error **error)
{
	if (is_parsing_arg((*tmp)->token))
	{
		if (is_parsing_separator((*error)->separator))
		{
			if ((*error)->before == 0)
				return (parse_error((*error)->separator));
			(*error)->after = 1;
			**error = init_error();
			(*error)->before = 1;
		}
		else
			(*error)->before = 1;
	}
	else if (is_parsing_separator((*tmp)->token))
	{
		if (is_parsing_separator((*error)->separator))
			return (parse_error((*tmp)->token));
		if ((*error)->before == 0)
			return (parse_error((*tmp)->token));
		(*error)->separator = (*tmp)->token;
	}
	return (1);
}

int			set_error(t_error *error, t_word *tmp)
{
	if (!no_error(&tmp, &error))
		return (0);
	if (is_last(tmp))
	{
		if (is_parsing_separator(error->separator) && error->separator != SEMICOL)
			return (2);
		if (is_parsing_separator(error->separator) && (!error->before || !error->after) && error->separator != SEMICOL)
			return (parse_error(error->separator));
	}
	return (1);
}