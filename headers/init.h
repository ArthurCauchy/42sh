/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 14:20:15 by acauchy           #+#    #+#             */
/*   Updated: 2018/11/14 11:40:02 by saxiao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __INIT_H
# define __INIT_H

# include "env.h"

/*
** init.c
*/

void	init(t_env **env, char **envp);

/*
** init_signals.h
*/

void	init_signals(void);

/*
** init_env.c
*/

void	init_env(t_env **env, char **envp);

/*
** init_builtins.c
*/

void	init_builtins(void);

/*
** init_history.c
*/

void	init_history(t_env **env);

/*
** init_termios.c
*/

void	init_termios(void);

#endif
