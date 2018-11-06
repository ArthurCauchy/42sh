/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 14:11:13 by acauchy           #+#    #+#             */
/*   Updated: 2018/11/06 16:46:54 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTS_H
# define REDIRECTS_H

# include "lexing.h"

typedef struct		s_redirect
{
	char				*left;
	char				*right;
	t_token				token;
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

void				add_redirect(t_redirect **redirs,
		char *left, char *right, t_token token);
int					analyze_redirects(t_word **arglist,
		t_redirect **redirs, char **errmsg);

/*
** redirections_fdsave.c
*/

void				save_filedes(int *fdtmp_array, int *fdsave_array, int fd);
void				restore_filedes(int *fdtmp_array, int *fdsave_array);

/*
** redirections_apply.c, redirections_apply_[token].c
*/

int					open_file_fd(char *filename, int mode,
		int append, char **errmsg);
int					apply_redirects(t_redirect *redirs,
		int *fdtmp_array, int *fdsave_array, char **errmsg);
int					apply_redirect_pipe(t_redirect *redir,
		int *fdtmp_array, int *fdsave_array, char **errmsg);
int					apply_redirect_lshift(t_redirect *redir,
		int *fdtmp_array, int *fdsave_array, char **errmsg);
int					apply_redirect_lshift_amp(t_redirect *redir,
		int *fdtmp_array, int *fdsave_array, char **errmsg);
int					apply_redirect_lshift2(t_redirect *redir,
		int *fdtmp_array, int *fdsave_array, char **errmsg);
int					apply_redirect_rshift(t_redirect *redir,
		int *fdtmp_array, int *fdsave_array, char **errmsg);
int					apply_redirect_rshift_amp(t_redirect *redir,
		int *fdtmp_array, int *fdsave_array, char **errmsg);
int					apply_redirect_rshift2(t_redirect *redir,
		int *fdtmp_array, int *fdsave_array, char **errmsg);

#endif
