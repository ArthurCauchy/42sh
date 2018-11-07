/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 14:20:15 by acauchy           #+#    #+#             */
/*   Updated: 2018/11/07 20:29:00 by lumenthi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __HISTORY_H
# define __HISTORY_H

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
void    history_add(char *cmd);
int     history_write_a(char *file);
int     history_write_t(char *file, char **hist);
void    history_clear(void);
void    history_exit(void);
int		exc_mark(char **str);

/*
** history_tools.c
*/

void		hist_null(char ***hist);
int			get_elems(char *line);
char		*read_file(int fd);
char		*to_string(char **ar);

/*
** history_init.c
*/

void		tab_scroll(char *cmd);
char		**history_read(char *filename, int start);
void		to_tab(char **line, char ***hist);
void		to_last(char **line, int start);

/*
** history_helper.c
*/

void		history_del(int elem);
char		*history_get(int elem);
void		history_add(char *cmd);

#endif
