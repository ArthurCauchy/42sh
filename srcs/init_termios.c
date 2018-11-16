/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_termios.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 12:56:09 by acauchy           #+#    #+#             */
/*   Updated: 2018/11/16 18:40:28 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <term.h>
#include "global.h"
#include "utils.h"

void	init_termios(void)
{
	char	*termtype;

	if (tcgetattr(0, &g_old_termios) == -1)
		exit_error("tcgetattr() error");
	termtype = read_from_env(&g_env, "TERM");
	if (termtype && tgetent(NULL, termtype) > 0)
		g_termcap_enabled = 1;
	else
		g_termcap_enabled = 0;
	free(termtype);
}
