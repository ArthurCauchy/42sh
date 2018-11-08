/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 14:20:15 by acauchy           #+#    #+#             */
/*   Updated: 2018/11/08 11:59:04 by lumenthi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __HISTORY_H
# define __HISTORY_H

# include "utils.h"
# include "env.h"

typedef struct	s_history
{
	int			position;
	int			size;
	char		*histfile;
	int			nb_lines;
	int			start;
	int			start_file;
	int			index;
	char		**line;
}				t_history;

char			**history_read(char *filename, int start);
void			history_del(int elem);
char			*history_get(int elem);
void			history_add(char *cmd);
int				history_write_a(char *file);
int				history_write_t(char *file, char **hist);
void			history_clear(void);
void			history_exit(void);
int				exc_mark(char **str);

/*
** history_tools.c
*/

void			hist_null(char ***hist);
int				get_elems(char *line);
char			*read_file(int fd);
char			*to_string(char **ar);

/*
** history_init.c
*/

void			tab_scroll(char *cmd);
char			**history_read(char *filename, int start);
void			to_tab(char **line, char ***hist);
void			to_last(char **line, int start);

/*
** history_helper.c
*/

void			history_del(int elem);
char			*history_get(int elem);
void			history_add(char *cmd);

/*
** builtin_history_error.c
*/

int				history_usage(char c);
int				del_error(int elem);
int				del_error_alpha(char elem);
int				requires_error(void);
int				read_error(char *file);

/*
** builtin_history_options.c
*/

int				history_d(char **args, int start);
int				history_r(char *file);
int				history_w(char *file);
int				history_p(char **args);
int				history_s(char **args);

/*
** builtin_history_messages.c
*/

int				multiple_afile(void);
int				args_error(char *str);
int				history_too_much(void);
int				history_numeric(void);
int				print_nhistory(int nb);

/*
** builtin_history_helper.c
*/

int				strchr_index(char *str, char *index);
char			*str_arg(char **args, int *start);
int				spe_free(char **str);
char			get_arg(char **args, int *start);
int				history_doclear(void);

/*
** builtin_history.c
*/

int				history_a(char *file);
int				history_n(char *file);
char			ret_char(char **str);
int				history_base(char **args, int start);
int				builtin_history(t_env **env, char **args);

#endif
