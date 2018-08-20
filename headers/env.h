/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 14:20:15 by acauchy           #+#    #+#             */
/*   Updated: 2018/08/20 18:21:44 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __ENV_H
# define __ENV_H

typedef struct		s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

/*
** s_env.c
*/

void				clear_env(t_env *env);
void				set_env(t_env **head, char *key, char *value);
void				unset_env(t_env **head, char *key);
t_env				*copy_env(t_env **env);

/*
** env.c
*/

void				print_env(t_env **env);
char				*read_from_env(t_env **env, char *key);
char				**env_to_array(t_env **env);

#endif
