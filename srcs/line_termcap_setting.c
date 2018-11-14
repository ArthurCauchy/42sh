/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_termcap_setting.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saxiao <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/27 17:30:47 by saxiao            #+#    #+#             */
/*   Updated: 2018/11/14 12:53:26 by saxiao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <termios.h>
#include <unistd.h>
#include "line_edit.h"
#include "global.h"

static void	default_termi_mode(void)
{
	struct termios	tattr;

	tcgetattr(STDIN_FILENO, &tattr);
	tattr.c_lflag |= (ECHO | ICANON | ISIG);
	tattr.c_oflag |= (OPOST);
	tcsetattr(STDIN_FILENO, TCSADRAIN, &tattr);
}

static void	for_attr(t_termios *old)
{
	struct termios new;
	
	new = *old;
	new.c_lflag &= ~(ECHO | ICANON | ISIG);
	new.c_oflag &= ~(OPOST);
	new.c_cc[VMIN] = 1;
	new.c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSADRAIN, &new);
}

/*
int			init_attr(int mod)
{
	static struct termios	old;
	static int				oldatt = 0;
	static char				*term = NULL;
	struct termios			new;

	if (term == NULL)
		term = read_from_env(&g_env, "TERM");
	if (!oldatt)
	{
		oldatt = 1;
		if (tcgetattr(0, &old) == -1)
			return (return_message("can't get att", -1, 2));
	}
	if (mod == ADVANCED_LINE_EDIT)
	{
		for_attr(&new, old);
		if (tgetent(NULL, term) != 1)
			return (freeterm_set2default(term));
	}
	else
		default_termi_mode();
	return (0);
}
*/

void		init_attr(int mod)
{
	if (g_termcap_enabled && mod == ADVANCED_LINE_EDIT)
		for_attr(&g_old_termios);
	else
		default_termi_mode();
}
