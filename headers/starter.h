/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   starter.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 14:11:13 by acauchy           #+#    #+#             */
/*   Updated: 2018/09/11 14:55:22 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STARTER_H
# define STARTER_H

# include "redirects.h"

typedef struct		s_process
{
	char				*path;
	char				**args;
	t_redirect	*redirs;
	//pid_t				pid;
}					t_process;

#endif
