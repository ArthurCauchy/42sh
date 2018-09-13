/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcap_setting.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saxiao <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/27 17:30:47 by saxiao            #+#    #+#             */
/*   Updated: 2018/09/13 14:37:40 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <termios.h>
#include <stdio.h>
#include <curses.h>
#include <term.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include "line_edit.h"

static int	return_message(char *message, int re_value, int fd)
{
	write(fd, message, ft_strlen(message));
	return (re_value);
}

static void	default_termi_mode(void)
{
	struct termios	tattr;

	tcgetattr(STDIN_FILENO, &tattr);
	tattr.c_lflag |= (ECHO | ICANON | ISIG);
	tattr.c_oflag |= (OPOST);
	tcsetattr(STDIN_FILENO, TCSADRAIN, &tattr);
}

static void	for_attr(struct termios *new, struct termios old)
{
	*new = old;
	new->c_lflag &= ~(ECHO | ICANON | ISIG);
	new->c_oflag &= ~(OPOST);
	new->c_cc[VMIN] = 1;
	new->c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSADRAIN, new);
}

int			init_attr(int mod)
{
	static struct termios	old;
	static int				oldatt = 0;
	struct termios			new;

	if (!oldatt)
	{
		oldatt = 1;
		if (tcgetattr(0, &old) == -1)
			return (return_message("can't get att", -1, 2));
	}
	if (mod == SETNEW)
	{
		for_attr(&new, old);
		if (tgetent(NULL, getenv("TERM")) != 1)
		{
			default_termi_mode();
			return (-1);
		}
	}
	else
		default_termi_mode();
	return (0);
}

int			my_putc(int c)
{
	write(1, &c, 1);
	return (0);
}
