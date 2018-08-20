/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_l_component.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 10:06:00 by acauchy           #+#    #+#             */
/*   Updated: 2018/08/20 17:54:14 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <stdlib.h>
#include "libft.h"
#include "utils.h"

void		add_to_compo_lst(t_list **list, char *buff)
{
	char	*str;
	char	**ptr;
	t_list	*new;

	if (ft_strlen(buff) < 1)
		return ;
	if (!(ptr = malloc(sizeof(char*))))
		exit_error("malloc() error");
	str = ft_strdup(buff);
	*ptr = str;
	new = ft_lstnew(ptr, sizeof(char*));
	free(ptr);
	ft_lstpushback(list, new);
}

void		remove_from_compo_lst(t_list **list, t_list *to_rm)
{
	t_list	*prev;
	t_list	*cur;

	prev = NULL;
	cur = *list;
	while (cur)
	{
		if (cur == to_rm)
		{
			if (cur == *list)
				*list = cur->next;
			prev->next = cur->next;
			free(*((char**)cur->content));
			free(cur->content);
			free(cur);
			return ;
		}
		prev = cur;
		cur = cur->next;
	}
}

t_list		*str_to_compo(char *str)
{
	t_list	*list;
	char	inslash;
	int		i;
	int		j;
	char	buff[PATH_MAX];

	list = NULL;
	inslash = 0;
	i = -1;
	j = 0;
	while (str[++i])
	{
		if ((!inslash && str[i] == '/') || (inslash && str[i] != '/'))
		{
			buff[j] = '\0';
			add_to_compo_lst(&list, buff);
			inslash = inslash ? 0 : 1;
			j = 0;
		}
		if (!inslash || j == 0)
			buff[j++] = str[i];
	}
	buff[j] = '\0';
	add_to_compo_lst(&list, buff);
	return (list);
}

char		*compo_to_str(t_list *list)
{
	t_list	*prev;
	char	buff[PATH_MAX * 2];
	char	c;
	size_t	i;
	size_t	j;

	prev = NULL;
	i = 0;
	while (list)
	{
		j = 0;
		while ((c = (*((char**)list->content))[j++]))
			buff[i++] = c;
		free(*((char**)list->content));
		free(list->content);
		prev = list;
		list = list->next;
		free(prev);
	}
	buff[i] = '\0';
	return (ft_strdup(buff));
}
