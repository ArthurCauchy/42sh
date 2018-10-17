/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_signals.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 12:56:09 by acauchy           #+#    #+#             */
/*   Updated: 2018/10/17 12:14:30 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>

void	init_signals(void)
{
	//signal(SIGINT, SIG_IGN); TEMPORARY DISABLED (for the sake of debug)
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGTTIN, SIG_IGN);
	signal(SIGTTOU, SIG_IGN);
}
