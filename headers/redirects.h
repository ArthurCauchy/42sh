/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 14:11:13 by acauchy           #+#    #+#             */
/*   Updated: 2018/10/18 19:50:11 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTS_H
# define REDIRECTS_H

# include "lexing.h"

typedef struct		s_redirect
{
	char							*left;
	char							*right;
	t_token						token;
	struct s_redirect	*next;
}					t_redirect;

#endif
