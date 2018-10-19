/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccharrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 16:53:03 by ccharrie          #+#    #+#             */
/*   Updated: 2018/10/19 17:12:43 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

typedef struct		s_alias
{
	char			*key;
	char			*value;
	struct s_alias	*next;
}					t_alias;

t_alias		*aliases = NULL;

void	alias_pushback(t_alias **new_alias)
{
	t_alias *head;
	
	head = aliases;
	if (!(aliases))
		aliases = *new_alias;
	else
	{
		while (aliases->next)
			aliases = aliases->next;
		aliases->next = *new_alias;
		aliases = head;
	}
}

void	display_aliases(void)
{
	t_alias *head;

	head = aliases;
	while (aliases)
	{
		ft_putstr(aliases->key);
		ft_putchar('=');
		ft_putendl(aliases->value);
		aliases = aliases->next;
	}
	aliases = head;
}

int		alias_exist(char *key, char *value)
{
	t_alias	*head;

	head = aliases;
	while (aliases)
	{
		if (ft_strcmp(aliases->key, key) == 0)
		{
			free(aliases->value);
			aliases->value = ft_strdup(value);
			aliases = head;
			return (0);
		}
		aliases = aliases->next;
	}
	aliases = head;
	return (1);
}

void	delete_alias(t_alias **prev, t_alias **aliases, t_alias **head,
		t_alias **tmp)
{
	if (*prev)
		(*prev)->next = (*aliases)->next;
	*tmp = (*aliases)->next;
	if (*aliases == *head)
		*head = (*aliases)->next;
	ft_multifree(3, (*aliases)->key, (*aliases)->value, *aliases);
	*aliases = *tmp;
}

void	unalias(char *line)
{
	t_alias *head;
	t_alias *tmp;
	t_alias	*prev;
	char	**split;
	char	**split2;

	split = ft_strsplit(line, ' ');
	split2 = ft_strsplit(split[1], '=');
	head = aliases;
	prev = NULL;
	while (aliases)
	{
		if (ft_strcmp(aliases->key, split2[0]) == 0)
			delete_alias(&prev, &aliases, &head, &tmp);
		else
		{
			prev = aliases;
			aliases = aliases->next;
		}
	}
	aliases = head;
}

int		alias_check(char **alias)
{
	int		len;

	len = -1;
	while (alias[++len]);
	if (len > 2)
	{	
		ft_putendl("rtfm noob, bad usage");
		return (0); 	//	insert alias usage here
	}
	else if (len < 2)
	{
		ft_putendl("missing fucking '='");
		return (0);
	}				 	//	insert missing '=' error
	len = -1;
	while (alias[0][++len])
	{
		if (!(ft_isalnum(alias[0][len])))
		{
			ft_putendl("did you thought you could trick me ? bad alphanum");
			return (0); // insert not alphanumeric error
		}
	}
	return (1);
}

#include "stdio.h" // TODO remove
void	alias(char	*line)
{
	char	**split;
	char	**split2;
	t_alias	*new_alias;
	
	split = ft_strsplit(line, ' ');
	split2 = ft_strsplit(split[1], '=');
	if (alias_exist(split2[0], split2[1]) && alias_check(split2))
	{
		if (!(new_alias = (t_alias *)malloc(sizeof(t_alias))))
			return ;
		new_alias->key = ft_strdup(split2[0]);
		new_alias->value = ft_strdup(split2[1]);
		new_alias->next = NULL;
		alias_pushback(&new_alias);
	}
//	free_tab();
}

/*int		main()
{
	char	*line;

	line = NULL;
	while (42)
	{
		get_next_line(0, &line);
		if (strcmp(line, "exit") == 0)
			break;
		else if (strcmp(line, "alias") == 0)
			display_aliases();
		else if (ft_strstr(line, "unalias"))
			unalias(line);
		else
			alias(line);
	}
	while (aliases)
	{
		printf("key : [%s]\nvalue : [%s]\n\n", aliases->key, aliases->value);
		aliases = aliases->next;
	}
	return (0);
}*/
