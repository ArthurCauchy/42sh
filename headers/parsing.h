/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 14:20:15 by acauchy           #+#    #+#             */
/*   Updated: 2018/10/17 17:06:49 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __PARSING_H
# define __PARSING_H

# include "lexing.h"

/*
** separator is the token separating this parse block with the next one.
** It must be one of the following :
** - PIPE
** - OR
** - AND
** - SEMICOL
** - NONE
*/

typedef struct	s_parse_block
{
	t_word					*wordlist;
	t_token					separator;
	struct s_parse_block	*next;
}				t_parse_block;

/*
** parsing.c
*/
void			free_parse_block(t_parse_block **parse); // TODO move to separate file 'parse_block.c'
t_parse_block	*new_parse_block(t_word *word, t_token separator); // same
t_parse_block	*do_parsing(t_word *wordlist, char **errmsg);

#endif
