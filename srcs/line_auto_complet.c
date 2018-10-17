/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_auto_complet.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saxiao <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/17 15:05:59 by saxiao            #+#    #+#             */
/*   Updated: 2018/10/17 15:25:08 by saxiao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <curses.h>
#include <term.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include "../libft/ft_printf/includes/ft_printf.h"
#include "../headers/line_edit.h"

static void	init_auto_start(int *i, int *find_start, int *res)
{
	*i = 0;
	*find_start = 0;
	*res = 0;
}

static void for_auto_start(char *line, int *i, int *open_squote, int *open_dquote)
{
	if (line[*i] == '"' && dslash_before(line, *i) && *open_squote < 0)
		*open_dquote = -*open_dquote;
	if (line[*i] == '\'' && dslash_before(line, *i) && *open_dquote < 0)
		*open_squote = -*open_squote;
	(*i)++;
}

int		auto_start(char *line)
{
	int		i;
	int		find_start;
	int		res;
	int		open_squote;
	int		open_dquote;

	open_squote = -1;
	open_dquote = -1;
	init_auto_start(&i, &find_start, &res);
	while (!find_start)
	{
		res = i;
		while (line[i] && !(open_squote < 0 && open_dquote < 0 && \
					(line[i] == ' ' || line[i] == '\t')))
			for_auto_start(line, &i, &open_squote, &open_dquote);
		if (!line[i])
			find_start = 1;
		else
			i++;
	}
	return (res);
}

int		auto_current(t_line *line)
{
	int		i;

	i = auto_start((char *)line->buf);
	if (!i)
		return (0);
	i--;
	while (i > 0 && line->buf[i] == ' ')
		i--;
	if (line->buf[i] != ' ' && line->buf[i] != '&' && line->buf[i] != '|')
		return (1);
	return (0);
}

t_autolist	*add_one_list(t_autolist *list, t_autolist *add)
{
	t_autolist	*cp;

	cp = list;
	if (!cp)
	{
		add->pre = NULL;
		add->ct = 0;
		return (add);
	}
	while (cp->next)
		cp = cp->next;
	add->pre = cp;
	add->ct = cp->ct + 1;
	cp->next = add;
	return (list);
}

/*
 ** Params :
 ** - list : autocompletion list
 ** - name : the name of this element of the list
 ** - type : 0 = regular file, 1 = directory
 */

t_autolist	*add_a_list(t_autolist *list, char *name, unsigned char type)
{
	t_autolist		*add;

	add = malloc(sizeof(t_autolist));
	add->next = NULL;
	ft_bzero(add->name, INPUT_MAX_LEN);
	ft_strcpy(add->name, name);
	add->len = ft_strlen(add->name);
	if (type == DT_DIR)
		add->is_dic = 1;
	else
		add->is_dic = 0;
	list = add_one_list(list, add);
	return (list);
}

int			buildin_exit(t_autolist *list, char *buildin)
{
	t_autolist		*cp;

	cp = list;
	while (cp)
	{
		if (!ft_strcmp(cp->name, buildin))
			return (1);
		cp = cp->next;
	}
	return (0);
}

t_autolist	*addlist_buildin(t_line *line, t_autolist *list)
{
	char			*buildin[7];
	int				i;

	buildin[0] = "cd";
	buildin[1] = "env";
	buildin[2] = "setenv";
	buildin[3] = "unsetenv";
	buildin[4] = "echo";
	buildin[5] = "exit";
	buildin[6] = NULL;
	i = -1;
	while (++i < 6)
	{
		if (!ft_strncmp((char *)line->auto_compare, buildin[i], ft_strlen((char *)line->auto_compare)) && !buildin_exit(list, buildin[i]))
			list = add_a_list(list, buildin[i], 0);
	}
	return (list);
}

t_autolist	*addlist_in_path(t_line *line, char **path, t_autolist *list)
{
	DIR				*dirp;
	struct dirent	*dir;

	while (path && *path)
	{
		if ((dirp = opendir(*path)))
		{
			while ((dir = readdir(dirp)))
			{
				if (!ft_strncmp((char *)line->auto_compare, dir->d_name, ft_strlen((char *)line->auto_compare)))
				{
					if (!(!ft_strlen((char *)line->auto_compare) && dir->d_name[0] == '.'))
						list = add_a_list(list, (char *)dir->d_name, dir->d_type);
				}
			}
			closedir(dirp);
		}
		path++;
	}
	if (!auto_current(line))
		list = addlist_buildin(line, list);
	return (list);
}

static void	path_last_slash(char *start, char *dic, int index)
{
	int		i;

	i = ft_strlen(start) - 1;
	while (i >= 0 && start[i] != '/')
		i--;
	ft_bzero(dic, index);
	ft_strncpy(dic, start, i + 1);
}

t_autolist	*addlist_no_path(t_line *line, t_autolist *list)
{
	DIR				*dirp;
	struct dirent	*dir;
	char			dic[INPUT_MAX_LEN];

	path_last_slash((char *)line->auto_compare, dic, INPUT_MAX_LEN);
	if ((dirp = opendir(dic)))
	{
		while ((dir = readdir(dirp)))
		{
			if (!ft_strncmp((char *)line->auto_compare + ft_strlen(dic), dir->d_name, ft_strlen((char *)line->auto_compare + ft_strlen(dic))))
				list = add_a_list(list, dir->d_name, dir->d_type);
		}
		closedir(dirp);
	}
	return (list);
}


t_autolist	*get_autolist(t_line *line, t_env **env)
{
	t_autolist	*list;
	char		**all_path;

	list = NULL;
	all_path = NULL;
	if (auto_current(line))
		all_path = ft_split("./", " ");
	else
		all_path = path(env);
	if (!ft_strchr((char *)line->auto_compare, '/'))
	{
		if (ft_strlen((char *)line->auto_compare) || !ft_strcmp(all_path[0], "./"))
			list = addlist_in_path(line, all_path, list);
	}
	else
		list = addlist_no_path(line, list);
	ft_freestrstr(all_path);
	return (list);
}

static	void	init_win(t_autolist *list, int win_col, t_win *win)
{
	t_autolist	*cp;

	cp = list;
	win->ct_lt = 0;
	win->max = 0;
	while (cp)
	{
		if (cp->len > win->max)
			win->max = cp->len;
		cp = cp->next;
	}
	win->max++;
	cp = list;
	while (cp)
	{
		(win->ct_lt)++;
		cp = cp->next;
	}
	win->col = win_col / win->max;
	if (!win->col)
		win->col = 1;
	win->line = win->ct_lt / win->col;
	if (win->ct_lt % win->col > 0)
		win->line++;
}

int		jump_list(t_line *line, int *total_row)
{
	int		row;
	int		nb_row_command;
	int		i;
	t_autolist	*cp;

	*total_row = line->w.line;
	i = line->auto_ct % nb_list(line->auto_lt) + 1;
	cp = line->auto_lt;
	while (--i > 0)
		cp = cp->next;
	nb_row_command = (line->buf_len + ft_strlen(cp->name) - ft_strlen((char *)line->auto_compare)- 1) / line->line_max + 1;
	if (line->screen_height - nb_row_command - line->w.line - 1 < 0)
		*total_row = line->screen_height - nb_row_command - 1;
	if (line->auto_ct < 0)
		return (0);
	row = line->auto_ct % nb_list(line->auto_lt) % line->w.line + 1;
	if (nb_row_command + row  + 1 <= line->screen_height)
		return (0);
	return (row  + 3 - line->screen_height - nb_row_command);
}

t_autolist	*start_list(t_line *line, int *total_row)
{
	int		i;
	t_autolist	*cp;

	i = jump_list(line, total_row) + 1;
	cp = line->auto_lt;
	while (--i > 0)
		cp = cp->next;
	return (cp);
}

void	put_colum(t_line *line)
{
	t_autolist	*cp;
	t_autolist	*lt;
	t_helper	ct;
	int			total_row;;

	ct.j = -1;
	total_row = line->w.line;
	lt = start_list(line, &total_row);
	while (++(ct.j) < total_row)
	{
		cp = lt;
		ct.i = -1;
		while (++(ct.i) < line->w.col && cp)
		{
			ct.index = 0;
			if (cp)
			{
				if (cp->ct == line->auto_ct % nb_list(line->auto_lt))
					bg_yellow();
				ft_printf("%-*s", line->w.max, cp->name);
				color_reset();
				line->auto_is_dic = cp->is_dic;
			}
			while (cp && (ct.index)++ < line->w.line)
				cp = cp->next;
		}
		ft_printf("\n");
		lt = lt->next;
	}
}

int	nb_list(t_autolist *list)
{
	int		i;

	i = 0;
	while (list)
	{
		i++;
		list = list->next;
	}
	return (i);
}

void	free_auto_lt(t_line *line)
{
	t_autolist *temp;

	while (line->auto_lt)
	{
		temp = line->auto_lt;
		line->auto_lt = line->auto_lt->next;
		free(temp);
	}
}

static void	put_first_lst(t_line *line)
{
	char	dic[INPUT_MAX_LEN];
	char	*str;

	if (ft_strchr((char *)line->auto_compare, '/'))
	{
		path_last_slash((char *)line->auto_compare, dic, INPUT_MAX_LEN);
		str = line->auto_lt->name + ft_strlen((char *)line->auto_compare) - ft_strlen(dic);
	}
	else
		str = line->auto_lt->name + ft_strlen((char *)line->auto_compare);
	while (*str)
		printable(line, *str++);
}

static void	put_choice_end(t_line *line, int chioce_isdic)
{
	if (chioce_isdic)
		printable(line, '/');
	else
		printable(line, ' ');
	free_auto_lt(line);
}

static void	one_autolist(t_line *line)
{
	put_first_lst(line);
	move_nright(line);
	put_choice_end(line, line->auto_lt->is_dic);
}

static void	put_choice(t_line *line, int *i)
{
	char		*str;
	t_autolist	*cp;
	int			auto_ct_saver;

	cp = line->auto_lt;
	auto_ct_saver = line->auto_ct;
	while (cp)
	{
		if (line->auto_ct % nb_list(line->auto_lt) == cp->ct)
		{
			if (line->auto_last_choice_len != -1)
			{
				*i = line->auto_last_choice_len + 1;
				while (--*i)
					delete_key(line);
			}
			if (line->auto_last_choice_len == -1)
				put_first_lst(line);
			else
			{
				str = cp->name;
				while (*str)
					printable(line, *str++);
			}
			line->auto_last_choice_len = ft_strlen(cp->name);
		}
		cp = cp->next;
	}
	line->auto_ct = auto_ct_saver;
}

void			clear_auto_onscreen(t_line *line)
{
	int		i;

	init_attr(BASIC_LINE_EDIT);
	ft_printf("\n");
	init_attr(ADVANCED_LINE_EDIT);
	tputs(tgetstr("cd", 0), 1, my_putc);
	tputs(tgetstr("up", 0), 1, my_putc);
	i = line->start_po + line->pos + 1;
	line->pos = 0 - line->start_po;
	while (--i)
		move_right(line);
}

void				is_tab(unsigned long key, t_line *line)
{
	if (key == TAB_KEY || (key_isarrow(key) && line->is_tabb4 == 1))
		line->is_tabb4 = 1;
	else
	{
		if (line->is_tabb4)
			clear_auto_onscreen(line);
		line->is_tabb4 = 0;
	}
}

static void	cusor_back(t_line *line)
{
	int		i;

	i = line->w.line + 2;
	init_attr(ADVANCED_LINE_EDIT);
	while (--i)
		tputs(tgetstr("up", 0), 1, my_putc);
	line->pos = 0 - line->start_po;
	move_nright(line);
	put_choice(line, &i);
}

int		return_key(t_line *line)
{
	line->auto_ct = -1;
	line->auto_last_choice_len = -1;
	move_nright(line);
	put_choice_end(line, line->auto_is_dic);
	clear_auto_onscreen(line);
	move_nright(line);
	return (0);
}

int		my_tabkey(t_line *line, t_env **env)
{
	ft_bzero((char *)line->auto_compare, INPUT_MAX_LEN);
	ft_strcpy((char *)line->auto_compare, (char *)line->buf + auto_start((char *)line->buf));
	if (line->auto_ct == -1)
	{
		free_auto_lt(line);
		line->auto_lt = get_autolist(line, env);
		init_win(line->auto_lt, line->line_max, &(line->w));
		sort_list(&line->auto_lt);
	}
	if (nb_list(line->auto_lt))
	{
		if (nb_list(line->auto_lt) == 1)
			one_autolist(line);
		else
		{
			init_attr(BASIC_LINE_EDIT);
			ft_printf("\n");
			init_attr(ADVANCED_LINE_EDIT);
			tputs(tgetstr("cd", 0), 1, my_putc);
			init_attr(BASIC_LINE_EDIT);
			put_colum(line);
			cusor_back(line);
			line->auto_ct = line->auto_ct + 1;;
		}
	}
	return (0);
}
