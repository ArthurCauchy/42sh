/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exc_mark.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumenthi <lumenthi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 16:43:06 by lumenthi          #+#    #+#             */
/*   Updated: 2018/11/06 16:56:59 by lumenthi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** exc_mark_return.c
*/

char	*return_before(char *str, int i);
char	*return_after(char *str, char **middle, int i);
int		return_middle(char **middle, char *before);

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