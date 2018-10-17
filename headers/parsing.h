/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 14:20:15 by acauchy           #+#    #+#             */
/*   Updated: 2018/10/17 15:54:01 by lumenthi         ###   ########.fr       */
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

void	delete_wordlist(t_word **head);
void	free_parse_block(t_parse_block **parse);

/*
** parsing.c
*/

t_parse_block *do_parsing(t_word *wordlist, char **errmsg);

// TODO define funtions here

#endif
