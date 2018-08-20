/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fminiprint.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/21 14:54:58 by acauchy           #+#    #+#             */
/*   Updated: 2017/12/21 16:05:27 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static void				(*get_print_fct(char given_type))(int, t_arg*, void*)
{
	if (given_type == 'd')
		return (&print_integer);
	else if (given_type == 's')
		return (&print_string);
	else
		return (&print_errortype);
}

static t_arg			*detect_arg(char *str)
{
	t_arg	*arg;
	int		i;

	if (!(arg = (t_arg*)malloc(sizeof(t_arg))))
		return (NULL);
	arg->alignleft = (str[1] == 'l') ? 1 : 0;
	arg->width = ft_atoi(str + 2);
	i = 2;
	while (ft_isdigit(str[i]))
		++i;
	arg->print_fct = get_print_fct(str[i]);
	return (arg);
}

/*
** Kind of mini printf func. Handle column formatting
** and left-align. Can be used with numbers and strings.
*/

void					ft_fminiprint(int fd, char *str, ...)
{
	va_list	ap;
	t_arg	*arg;

	va_start(ap, str);
	arg = NULL;
	while (*str)
	{
		if (*str == '%')
		{
			if (*(++str) == '%')
				ft_putchar_fd('%', 2);
			else
			{
				arg = detect_arg(str - 1);
				arg->print_fct(fd, arg, va_arg(ap, void*));
				free(arg);
			}
			while (*str != '%')
				++str;
		}
		else
			ft_putchar_fd(*str, fd);
		++str;
	}
	va_end(ap);
}
