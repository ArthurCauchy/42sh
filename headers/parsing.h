/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 14:20:15 by acauchy           #+#    #+#             */
/*   Updated: 2018/11/09 18:42:00 by lumenthi         ###   ########.fr       */
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
	int						before;
	int						after;
	t_token					separator;
	char					*msg;
}				t_error;

/*
** parse_block.c
*/

void			word_push(t_word **wordlist, t_word *new_word);
void			block_push(t_parse_block **blocklist, t_parse_block *new_block);
void			free_parse_block(t_parse_block **parse);
t_parse_block	*new_parse_block(t_word *word, t_token separator);
t_parse_block	*clone_parse_block(t_parse_block *orig);

/*
** parsing_error.c
*/

t_error			init_error(void);
int				set_error(t_error *error, t_word *tmp);
void			main_parsing(t_word **cmd_args, t_parse_block **parsed,
				char **errmsg, char **input);
/*
** parsing.c
*/

int				is_last(t_word *wordlist);
int				is_parsing_separator(t_token elem);
int				is_parsing_arg(t_token elem);
void			free_parse_block(t_parse_block **parse);
t_parse_block	*new_parse_block(t_word *word, t_token separator);
int				do_parsing(t_word *wordlist,
				t_parse_block **parsing, char **errmsg);

/*
** main.c
*/

void			recursive_main_loop(char **input);

/*
** parse_block_clone.c
*/

t_parse_block	*clone_parse_block(t_parse_block *orig);
int				is_last(t_word *wordlist);
int				is_parsing_separator(t_token elem);
int				is_parsing_arg(t_token elem);

#endif
