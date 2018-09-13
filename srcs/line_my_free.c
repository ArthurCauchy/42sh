/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saxiao <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/27 15:56:54 by saxiao            #+#    #+#             */
/*   Updated: 2018/09/13 15:10:17 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "line_edit.h"

/*
void	free_sh_table(t_sh *table, int index)
{
	int			i;
	t_table		*cp;
	t_table		*temp;

	i = 0;
	while (i < index)
	{
		if (table[i].sh_ta)
		{
			cp = table[i].sh_ta;
			while (cp)
			{
				temp = cp;
				cp = cp->next;
				free(temp);
			}
		}
		table[i].sh_ta = NULL;
		i++;
	}
}
*/
void	ft_freestrstr(char **str)
{
	char	**temp;

	if (str)
	{
		temp = str;
		while (*str)
		{
			free(*str);
			str++;
		}
		free(temp);
	}
}

/*
void	free_pro_args(t_program *pro, int index)
{
	int		i;

	i = -1;
	while (++i < index && pro[i].pro_args)
		free(pro[i].pro_args);
}

void	free_word_list(t_word *list)
{
	t_word *temp;

	while (list)
	{
		temp = list;
		list = list->next;
		free(temp);
	}
}
*/
