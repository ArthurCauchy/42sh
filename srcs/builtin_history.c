/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_history.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 10:06:00 by acauchy           #+#    #+#             */
/*   Updated: 2018/08/20 18:03:52 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "utils.h"
#include "env.h"
#include "global.h"

/*int			builtin_history(t_env **env, char **args)
{
	int			i;
	char		options[4096];

	(void)env;
	(void)i;
	i = builtin_parse_options(args, options, 4096);
	if (builtin_validate_options(options, "acdrnpsw") == -1) // probably need to check for incompatible options too
	{
		ft_putendl_fd("Usage : history AND SOME OPTIONS", 2); //TODO
		return (1);
	}
	ft_putstr("Options found :");
	ft_putendl(options);
	return (0);
}*/

static int	history_doclear(void)
{
	g_history->history_clear();
	ft_putendl("Cleaning history...");
	return (1);
}

static int	history_usage(char c)
{
	ft_putstr_fd("history: illegal option ", 2);
	ft_putchar_fd(c, 2);
	ft_putchar_fd('\n', 2);
	ft_putendl_fd("usage: history [-c] [-d offset] [n]", 2);
	ft_putendl_fd("       history -anrw [filename]", 2);
	ft_putendl_fd("       history -ps arg [arg ...]", 2);
	return (1);
}

static int	strchr_index(char *str, char *index)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (ft_strchr_index(index, str[i]) == -1)
			return (str[i]);
		i++;
	}
	return (0);
}

int		print_nhistory(int nb)
{
	int i;
	int start;

	i = 0;
	start = g_history->nb_lines - nb;
	ft_putendl("history:\n");
	if (g_history->nb_lines <= 0)
		return (1);
	while (g_history->line[i])
	{
		if (i >= start)
		{
			ft_putnbr((i + 1) + g_history->index);
			ft_putstr(" - [");
			ft_putstr(g_history->line[i]);
			ft_putendl("]");
		}
		i++;
	}
	return (0);
}

static int		del_error(int elem)
{
	ft_putstr_fd("history: ", 2);
	ft_putnbr_fd(elem, 2);
	ft_putstr_fd(": position out of range\n", 2);
	return (1);
}

static int		del_error_alpha(char elem)
{
	ft_putstr_fd("history: ", 2);
	ft_putchar_fd(elem, 2);
	ft_putstr_fd(": position out of range\n", 2);
	return (1);
}

static int		requires_error(void)
{
	ft_putendl_fd("history -d: option requires an argument", 2);
	return (1);
}

int			history_d(char **args, int start)
{
	int	i;
	int	new;
	int	elem;

	if (!(args[start]))
		return (requires_error());
	if ((i = strchr_index(args[start], "0123456789")) ||
		ft_strcmp(args[start], "") == 0)
		return (del_error_alpha(i));
	elem = ft_atoi(args[start]);
	i = 0;
	new = (elem - g_history->index) - 1;
	if (g_history->nb_lines == g_history->SIZE && new == -1)
		return (0);
	else if (new < 0 || new > (g_history->nb_lines - 1))
		return (del_error(elem));
	g_history->history_del(new);
	return (0);
}

static int	read_error(char *file)
{
	ft_putstr_fd("history: can't read ", 2);
	ft_putendl_fd(file, 2);
	return (1);
}

int			history_r(char *file)
{
	char	**ta;
	int		i;

	i = 0;
	if (file == NULL || ft_strcmp(file, "") == 0)
		ta = g_history->history_read(HISTFILE, 0);
	else
		ta = g_history->history_read(file, 0);
	if (ta == NULL)
		return (read_error(file));
	while (ta[i])
	{
		g_history->history_add(ta[i]);
		free(ta[i]);
		i++;
	}
	free(ta);
	return (0);
}

int		history_w(char *file)
{
	int ret;

	ret = 0;
	if (file == NULL || ft_strcmp(file, "") == 0)
	{
		ret = g_history->history_writeT(HISTFILE, g_history->line);
		g_history->start = g_history->nb_lines;
	}
	else
		ret = g_history->history_writeT(file, g_history->line);
	return (ret = 1 ? 0 : 1);
}

int			history_p(char **args)
{
	int i;

	i = 2;
	if (args[i])
		g_history->history_del(g_history->nb_lines - 1);
	while (args[i])
		ft_putendl(args[i++]);
	return (0);
}

int			history_s(char **args)
{
	int		i;
	char	*str;

	i = 2;
	if (args[i])
	{
		g_history->history_del(g_history->nb_lines - 1);
		str = ft_strdup("");
		while (args[i])
		{
			str = ft_strjoinl(str, args[i++]);
			if (args[i])
				str = ft_strjoinl(str, " ");
		}
		g_history->history_add(str);
		free(str);
	}
	return (0);
}

int			history_a(char *file)
{
	return (g_history->history_writeA(file));
}

int			history_n(char *file)
{
	char	**add;
	int		i;

	i = 0;
	if (file == NULL || ft_strcmp(file, "") == 0)
		add = g_history->history_read(HISTFILE, g_history->start_file);
	else
		add = g_history->history_read(file, g_history->start_file);
	if (add == NULL)
		return (1);
	while (add[i])
	{
		g_history->history_add(add[i]);
		free(add[i]);
		i++;
	}
	free(add);
	return (0);
}

static char	*str_arg(char **args, int *start)
{
	char	*str;
	char	*tmp;
	int		i;

	str = ft_strdup("");
	while (args[*start] && args[*start][0] == '-')
	{
		i = 1;
		while (args[*start][i])
		{
			tmp = ft_strdup(str);
			free(str);
			str = ft_charjoin(tmp, args[*start][i]);
			free(tmp);
			i++;
		}
		(*start)++;
	}
	return (str);
}

static int	multiple_afile(void)
{
	ft_putendl_fd("history: cannot use more than one of -anrw", 2);
	return (1);
}

static int	args_error(char *str)
{
	int		i;
	int		count;
	char	c;

	i = 0;
	count = 0;
	if (((c = strchr_index(str, "cdanrwps")) > 0) && history_usage(c))
		return (1);
	if (strchr_index(str, "cdps") == 0)
		return (0);
	while (str[i])
	{
		if (ft_strchr_index("anrw", str[i]) != -1)
			count++;
		i++;
	}
	if (count > 1)
		return (multiple_afile());
	return (0);
}

static int	spe_free(char **str)
{
	free(*str);
	return (1);
}

static char	ret_char(char **str)
{
	if (ft_strchr(*str, 'c') && spe_free(str))
		return ('c');
	else if (ft_strchr(*str, 'd') && spe_free(str))
		return ('d');
	else if (ft_strchr(*str, 's') && spe_free(str))
		return ('s');
	else if (ft_strchr(*str, 'p') && spe_free(str))
		return ('p');
	else if (ft_strchr(*str, 'a')  && spe_free(str))
		return ('a');
	else if (ft_strchr(*str, 'n')  && spe_free(str))
		return ('n');
	else if (ft_strchr(*str, 'r')  && spe_free(str))
		return ('r');
	else if (ft_strchr(*str, 'w')  && spe_free(str))
		return ('w');
	return ('0');
}

static char	get_arg(char **args, int *start)
{
	char *str;

	if (args_size(args) == 1)
		return ('0');
	str = str_arg(args, start);
	if (*start == 1 && spe_free(&str))
		return ('0');
	if (!args_error(str))
		return (ret_char(&str));
	else if (spe_free(&str))
		return ('e');
	free(str);
	return ('0');
}

static int	history_too_much(void)
{
	ft_putendl_fd("history: too many arguments", 2);
	return (1);
}

static int	history_numeric(void)
{
	ft_putendl_fd("history: numeric argument required", 2);
	return (1);
}

static int	history_base(char **args, int start)
{
	int		i;

	i = 0;
	if (args[start] == NULL)
		return (print_nhistory(g_history->nb_lines));
	else
	{
		while (args[start + i])
		{
			if (strchr_index(args[start + i], "0123456789") ||
				ft_strcmp(args[start + i], "") == 0)
				return (history_numeric());
			i++;
		}
		if (i > 1)
			return (history_too_much());
		return (print_nhistory(ft_atoi(args[start])));
	}
}

int			builtin_history(t_env **env, char **args)
{
	int		start;
	char	arg;

	(void)env;
	start = 1;
	arg = get_arg(args, &start);
	if (arg == '0')
		return (history_base(args, start));
	else if (arg == 'c')
		return (history_doclear());
	else if (arg == 'r')
		return (history_r(args[start]));
	else if (arg == 'a')
		return (history_a(args[start]));
	else if (arg == 'n')
		return (history_n(args[start]));
	else if (arg == 'w')
		return (history_w(args[start]));
	else if (arg == 'p')
		return (history_p(args));
	else if (arg == 's')
		return (history_s(args));
	else if (arg == 'd')
		return (history_d(args, start));
	else
		return (1);
}
