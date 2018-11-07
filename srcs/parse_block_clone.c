/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_block_clone.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumenthi <lumenthi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 13:58:39 by lumenthi          #+#    #+#             */
/*   Updated: 2018/11/07 13:58:52 by lumenthi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "libft.h"
#include <stdlib.h>

t_parse_block	*clone_parse_block(t_parse_block *orig)
{
	return (new_parse_block(copy_wordlist(orig->wordlist), orig->separator));
}