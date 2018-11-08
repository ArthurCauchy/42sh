/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 14:11:13 by acauchy           #+#    #+#             */
/*   Updated: 2018/11/08 22:04:46 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "libft.h"
# include "env.h"

# define EXIT_USAGE "exit [return status]"
# define CD_USAGE "cd [-l|-p] [dir]"
# define ENV_USAGE "env [-i] [var=value ...] [cmd]"
# define SETENV_USAGE "setenv [var] [value]"
# define UNSETENV_USAGE "unsetenv [var ...]"
# define ECHO_USAGE "echo [arg ...]"
# define WHICH_USAGE "which [cmd]"
# define HELP_USAGE "help [builtin]"
# define HISTORY_USAGE1 "history [-c] [-d offset] [n]\n"
# define HISTORY_USAGE2 "history -anrw [filename]\n"
# define HISTORY_USAGE3 "history -ps arg [arg ...]"
# define HISTORY_USAGE HISTORY_USAGE1 HISTORY_USAGE2 HISTORY_USAGE3
# define ALIAS_USAGE "alias [-a] or [name='value']"
# define UNALIAS_USAGE "unalias [name]"

# define EXIT_BRIEF "Exit the shell."
# define CD_BRIEF "Change the shell working directory."
# define ENV_BRIEF1 "Start a command with a custom environment, "
# define ENV_BRIEF2 "or just print it if no command is specified."
# define ENV_BRIEF ENV_BRIEF1 ENV_BRIEF2
# define SETENV_BRIEF "Set an environment variable."
# define UNSETENV_BRIEF "Unset given environment variables."
# define ECHO_BRIEF "Write arguments to the standard output."
# define WHICH_BRIEF "Show the full path of an executable."
# define HELP_BRIEF "Print the help page of a builtin."
# define HISTORY_BRIEF "Display or manipulate the history list."
# define ALIAS_BRIEF1 "Create an alias, aliases allow a string to be"
# define ALIAS_BRIEF2 " substituted for a word when it is used as the first"
# define ALIAS_BRIEF3 " word of a simple command."
# define ALIAS_BRIEF ALIAS_BRIEF1 ALIAS_BRIEF2 ALIAS_BRIEF3
# define UNALIAS_BRIEF "Delete an alias, -a option delete all alias."

# define EXIT_HELP EXIT_USAGE "\n\n" EXIT_BRIEF
# define CD_HELP CD_USAGE "\n\n" CD_BRIEF
# define ENV_HELP ENV_USAGE "\n\n" ENV_BRIEF
# define SETENV_HELP SETENV_USAGE "\n\n" SETENV_BRIEF
# define UNSETENV_HELP UNSETENV_USAGE "\n\n" UNSETENV_BRIEF
# define ECHO_HELP ECHO_USAGE "\n\n" ECHO_BRIEF
# define WHICH_HELP WHICH_USAGE "\n\n" WHICH_BRIEF
# define HELP_HELP HELP_USAGE "\n\n" HELP_BRIEF
# define HISTORY_HELP HISTORY_USAGE "\n\n" HISTORY_BRIEF
# define ALIAS_HELP ALIAS_USAGE "\n\n" ALIAS_BRIEF
# define UNALIAS_HELP UNALIAS_USAGE "\n\n" UNALIAS_BRIEF

typedef struct		s_builtin
{
	char	*name;
	char	*brief;
	int		(*func)(t_env**, char**);
}					t_builtin;

typedef struct		s_alias
{
	char			*key;
	char			*value;
	struct s_alias	*next;
}					t_alias;

typedef int	(*t_builtin_fct)(t_env**, char**);

/*
** builtins_manager.c
*/

t_builtin			**get_builtins(void);
void				clear_builtins(void);
void				load_builtin(char *name, char *brief,
		int (*func)(t_env**, char**));
t_builtin			*search_builtin(char *name);

/*
** builtins_utils.c
*/

int					builtin_parse_options(char **args,
		char *options, int options_size);
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
int					builtin_history(t_env **env, char **args);
int					builtin_alias(t_env **env, char **args);
int					builtin_unalias(t_env **env, char **args);

/*
** builtin_cd[...].c
*/

void				print_chdir_error(char *path);
char				*search_cdpath(t_env **env, char *path);
int					try_cd_l(t_env **env, char *path);
int					try_cd_p(t_env **env, char *path);
void				add_to_compo_lst(t_list **list, char *buff);
void				remove_from_compo_lst(t_list **list, t_list *to_rm);
t_list				*str_to_compo(char *str);
char				*compo_to_str(t_list *list);
void				simplify_path_dot(t_list **list);
void				simplify_path_dotdot(t_list **list);
void				simplify_path_slash(t_list **list);

/*
** builtin_alias
*/

int					check_alias_existance(char *key, char *value);
int					check_alias_forbid_char(char *value);

#endif
