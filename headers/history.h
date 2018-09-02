/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 14:20:15 by acauchy           #+#    #+#             */
/*   Updated: 2018/08/20 18:21:44 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __HISTORY_H
# define __HISTORY_H

typedef struct	s_history
{
	int			(*history_init)(void);
	//historic initialisation, put at the beginning of program
	void		(*history_add)(char *);
	//add value at the end of the history list
	void		(*history_clear)(void);
	//clear the whole history list
	char		*(*history_get)(int);
	//return specified value from the list
	void		(*history_del)(int);
	//delete specified elem from the list
	void		(*history_exit)(void);
	//free everything and write content to HISTFILE
	int			(*history_writeA)(char *);
	//write (append) current history list to specified file
	int			(*history_writeT)(char *, char **);
	//write (trunc) HIST list to specified file
	char		**(*history_read)(char *, int);
	//return read lines from a file

	int			position;
	//save current position when browsing history list (up, down arrow key)
	int			SIZE;
	//= HISTSIZE
	int			nb_lines;
	//nb of lines in our current history tab
	int			start;
	//number of our starting elem
	int			start_file;
	//number of the last line read from HISTFILE
	int			index;
	//when displaying our history, gives us the real elem number
	char		**line;
	//tab where commands are stored
}								t_history;

char    **history_read(char *filename, int start);
void    history_del(int elem);
char    *history_get(int elem);
void    history_add(char *cmd);
int     history_writeA(char *file);
int     history_writeT(char *file, char **hist);
void    history_clear(void);
void    history_exit(void);
int     init_history(void);

#endif
