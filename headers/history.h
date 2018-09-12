/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 14:20:15 by acauchy           #+#    #+#             */
/*   Updated: 2018/09/11 22:07:20 by lumenthi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __HISTORY_H
# define __HISTORY_H

typedef struct	s_history
{
	int			position;
	//save current position when browsing history list (up, down arrow key)
	int			SIZE;
	//= HISTSIZE
	char		*HISTFILE;
	//= HISTFILE
	int			nb_lines;
	//nb of lines in our current history tab
	int			start;
	//number of our starting elem
	int			start_file;
	//number of the last line read from HISTFILE
	int			index;
	//when displaying our history, gives us the real elem number
	char		**line;
	//array where commands are stored
}								t_history;

char    **history_read(char *filename, int start);
void    history_del(int elem);
char    *history_get(int elem);
void    history_add(char *cmd);
int     history_writeA(char *file);
int     history_writeT(char *file, char **hist);
void    history_clear(void);
void    history_exit(void);
int		exc_mark(char **str); //exc_mark function

#endif
