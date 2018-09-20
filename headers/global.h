/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 14:20:15 by acauchy           #+#    #+#             */
/*   Updated: 2018/09/20 15:54:25 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __GLOBAL_H
# define __GLOBAL_H

# include "env.h"
# include "history.h"

extern t_env			*g_env;
extern t_history	*g_history;
extern int			g_with_termcap;

#endif
