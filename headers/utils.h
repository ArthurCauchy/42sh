/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 14:20:15 by acauchy           #+#    #+#             */
/*   Updated: 2018/09/13 16:56:50 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __UTILS_H
# define __UTILS_H

# define INPUT_MAX_LEN 10000
# define PARAMS_MAX 1024
# define BUILTINS_MAX 42
# define HISTSIZE 500

# include "lexing.h"

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

/*
** utils_args.c
*/

int		args_size(char **args);
void	arglist_to_array(t_word *arglist, char **args);
char	**copy_args(char **args);
void	delete_args(char **args);

#endif
