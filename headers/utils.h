/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 14:20:15 by acauchy           #+#    #+#             */
/*   Updated: 2018/11/16 18:24:28 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __UTILS_H
# define __UTILS_H

# define INPUT_MAX_LEN 10000
# define PARAMS_MAX 1024
# define BUILTINS_MAX 42
# define FD_MAX 1024
# define HISTSIZE 500
# define MAX_HEREDOC_TMP 512

# include <termios.h>
# include "lexing.h"

/*
** Typedef for termios
*/

typedef	struct termios	t_termios;

/*
** utils.c
*/

void	exit_error(char *errmsg);
int		is_there_a_file(char *filepath);
int		is_executable(char *filepath);
int		is_directory(char *filepath);
int		is_separator(char c);

/*
** utils2.c
*/

void	print_n_free_errmsg(char **errmsg);
char	*get_alias_value(char *key);

/*
** utils_args.c
*/

int		args_size(char **args);
char	**arglist_to_array(t_word *arglist);
char	**copy_args(char **args);
void	delete_args(char **args);

/*
** utils_signals.c
*/

void	reset_sighandlers(void);

/*
** utils_process.c
*/

int		get_process_return(int status);

/*
** utils_vars.c
*/

void	apply_var_substitution(t_word *wordlist);

#endif
