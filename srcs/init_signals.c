/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_signals.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 12:56:09 by acauchy           #+#    #+#             */
/*   Updated: 2018/10/19 15:53:46 by saxiao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <curses.h>
#include <term.h>
#include "line_edit.h"
#include "../headers/global.h"

void	handle_winch(int signo)
{
	if (signo == SIGWINCH)
	{
//		if (g_with_termcap)
			tputs(tgetstr("rs", 0), 1, my_putc);
		g_winsize_changed = 1;
		}
}

void	init_signals(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGTTIN, SIG_IGN);
	signal(SIGTTOU, SIG_IGN);
	signal(SIGWINCH, handle_winch);
}
