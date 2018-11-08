/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exc_mark.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumenthi <lumenthi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 16:43:06 by lumenthi          #+#    #+#             */
/*   Updated: 2018/11/08 11:35:19 by lumenthi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __EXC_MARK_H
# define __EXC_MARK_H

/*
** exc_mark_return.c
*/

char	*return_before(char *str, int i);
char	*return_after(char *str, char **middle, int i);
int		return_middle(char **middle, char *before);

/*
** exc_mark.c
*/

void	fill_inter(char *str, char **middle, int *i);

/*
** exc_mark_fill.c
*/

void	fill_digit(char *str, char **middle, int *i);
void	fill_alpha(char *str, char **middle, int *i);
void	fill_one(char *str, char **middle, int *i);
void	fill_minus(char *str, char **middle, int *i);
void	fill_other(char *str, char **middle, int *i);

/*
** exc_mark_tools.c
*/

int		check_matches(char *str1, char *str2);
int		is_backslash(char *str, int pos, int s_quote);
int		is_legit(char *str, int pos);
char	*exc_error(char *str);
char	*ft_add(char *before, char *middle, char *after);

/*
** exc_mark_get.c
*/

char	*get_digit(char *middle);
char	*get_alpha(char *middle);
char	*get_minus(char *middle);
char	*get_exc(char *middle);
char	*get_inter(char *middle);

#endif
