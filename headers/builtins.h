/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 14:11:13 by acauchy           #+#    #+#             */
/*   Updated: 2018/08/25 19:21:41 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "libft.h"
# include "env.h"

# define EXIT_USAGE "exit [return status]"
# define CD_USAGE "cd [-l|-p] [dir]"
# define ENV_USAGE "env [-i] [var=value ...] [cmd]"
# define ECHO_USAGE "echo [arg ...]"

# define EXIT_BRIEF "Exit the shell."
# define CD_BRIEF "Change the shell working directory."
# define ECHO_BRIEF "Write arguments to the standard output."

# define EXIT_HELP EXIT_USAGE "\n\n" EXIT_BRIEF
# define CD_HELP CD_USAGE "\n\n" CD_BRIEF
# define ENV_HELP ENV_USAGE
# define ECHO_HELP ECHO_USAGE "\n\n" ECHO_BRIEF

typedef struct		s_builtin
{
	char	*name;
	char	*brief;
	int		(*func)(t_env**, char**);
}					t_builtin;

typedef int	(*t_builtin_fct)(t_env**, char**);

/*
** builtins_manager.c
*/

t_builtin			**get_builtins(void);
void				clear_builtins(void);
void				load_builtin(char *name, char *brief, int (*func)(t_env**, char**));
t_builtin			*search_builtin(char *name);

/*
** builtins_utils.c
*/

int					builtin_parse_options(char **args, char *options, int options_size);
int					builtin_validate_options(char *options, char *valid_set);

/*
** builtin_[builtin_name].c
*/

int					builtin_exit(t_env **env, char **args);
int					builtin_cd(t_env **env, char **args);
int					builtin_env(t_env **env, char **args);
int					builtin_setenv(t_env **env, char **args);
int					builtin_unsetenv(t_env **env, char **args);
int					builtin_echo(t_env **env, char **args);
int					builtin_which(t_env **env, char **args);
int					builtin_help(t_env **env, char **args);

/*
** builtin_cd[...].c
*/

void				print_chdir_error(char *path);
int					try_cd_l(t_env **env, char *path);
int					try_cd_p(t_env **env, char *path);
void				add_to_compo_lst(t_list **list, char *buff);
void				remove_from_compo_lst(t_list **list, t_list *to_rm);
t_list				*str_to_compo(char *str);
char				*compo_to_str(t_list *list);
void				simplify_path_dot(t_list **list);
void				simplify_path_dotdot(t_list **list);
void				simplify_path_slash(t_list **list);

#endif
