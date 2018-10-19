/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 14:11:13 by acauchy           #+#    #+#             */
/*   Updated: 2018/10/19 15:11:16 by acauchy          ###   ########.fr       */
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

/*
** redirects.c
*/

t_redirect			*new_redirect(char *left, char *right, t_token token);
void				delete_redirects(t_redirect *redirs);

/*
** redirections.c
*/

void				add_redirect(t_redirect **redirs, char *left, char *right, t_token token);
int					analyze_redirects(t_word **arglist, t_redirect **redirs, char **errmsg);

#endif
