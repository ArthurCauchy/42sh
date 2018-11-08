/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_block_clone.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumenthi <lumenthi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 13:58:39 by lumenthi          #+#    #+#             */
/*   Updated: 2018/11/08 11:28:58 by lumenthi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "libft.h"
#include <stdlib.h>

t_parse_block	*clone_parse_block(t_parse_block *orig)
{
	return (new_parse_block(copy_wordlist(orig->wordlist), orig->separator));
}

int				is_last(t_word *wordlist)
{
	if (wordlist->next == NULL)
		return (1);
	return (0);
}

int				is_parsing_separator(t_token elem)
{
	if (elem == PIPE || elem == OR || elem == AND || elem == SEMICOL)
		return (1);
	return (0);
}

int				is_parsing_arg(t_token elem)
{
	if (elem == ARG)
		return (1);
	return (0);
}
