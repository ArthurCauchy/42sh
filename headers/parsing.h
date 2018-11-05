/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 14:20:15 by acauchy           #+#    #+#             */
/*   Updated: 2018/11/05 12:49:27 by lumenthi         ###   ########.fr       */
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

typedef struct	s_error
{
	int			before;
	int			after;
	t_token		separator;
	char		*msg;
}				t_error;

/*
** parse_block.c
*/

void			word_push(t_word **wordlist, t_word *new_word);
void			block_push(t_parse_block **blocklist, t_parse_block *new_block);
void			free_parse_block(t_parse_block **parse);
t_parse_block	*new_parse_block(t_word *word, t_token separator);
t_parse_block*	clone_parse_block(t_parse_block *orig);

/*
** parsing.c
*/
void			free_parse_block(t_parse_block **parse); // TODO move to separate file 'parse_block.c'
t_parse_block	*new_parse_block(t_word *word, t_token separator); // same
int				do_parsing(t_word *wordlist, t_parse_block **parsing, char **errmsg);

#endif