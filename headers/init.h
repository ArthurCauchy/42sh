/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 14:20:15 by acauchy           #+#    #+#             */
/*   Updated: 2018/08/22 09:10:19 by arthur           ###   ########.fr       */
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

void	init_history(void);

#endif
