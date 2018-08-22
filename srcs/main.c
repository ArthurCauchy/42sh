/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/20 12:03:19 by acauchy           #+#    #+#             */
/*   Updated: 2018/08/22 09:33:31 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "libft.h"
#include "utils.h"
#include "env.h"
#include "init.h"

// TEMPORARY AND UNPROTECTED input loop

static char	*ask_for_input(void)
{
	static char	buff[16384];
	int			size_read;
	char		*ret;

	ret = NULL;
	ft_putstr("$> ");
	size_read = read(0, buff, 16384);
	if (size_read == -1)
		exit_error("read() error");
	buff[size_read] = '\0';
	if (size_read > 0 && buff[size_read - 1] == '\n')
		buff[size_read - 1] = '\0';
	ret = ft_strdup(buff);
	return (ret);
}

int			main(int argc, char **argv, char **envp)
{
	t_env	*env;
	char	*input;

	(void)argc;
	(void)argv;
	env = NULL;
	init(&env, envp);
	while ((input = ask_for_input()) != NULL)
	{
		ft_putendl(input);
	}
	return (0);
}
