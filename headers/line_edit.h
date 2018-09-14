/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_edit.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saxiao <saxiao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/29 00:15:00 by saxiao            #+#    #+#             */
/*   Updated: 2018/09/14 12:39:27 by lumenthi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LINE_EDIT_H
# define LINE_EDIT_H

# include <sys/types.h>
# include <limits.h>
# include "libft.h"
# include "utils.h"

int		g_open_dquote;
int		g_open_squote;
int		g_open_backslash;
int		g_end_line;
int		g_with_termcap;
int		g_inside_doc_quote;
int		g_clc;
int		g_dld;

# define SETNEW 1
# define SETOLD 0
# define NOT_DIR 0
# define STDIN_FILENO 0
# define STDOUT_FILENO 1
# define NB_KEY 21
# define ARROW_LEFT 4479771
# define ARROW_RIGHT 4414235
# define ARROW_UP 4283163
# define ARROW_DOWN 4348699
# define MY_DELECT 127
# define MY_HOME 4741915
# define MY_END 4610843
# define CT_SHIFT_LEFT 74999712013083
# define CONTRL_L 12
# define CONTRL_H 8
# define CONTRL_A 1
# define CONTRL_B 2
# define CONTRL_E 5
# define CONTRL_P 16
# define ALT_M 46530
# define CONTRL_PERCENT 29
# define ALT_S 40899
# define ALT_UP 1096489755
# define ALT_DOWN 1113266971
# define OPTION_SHIFT_U 43202
# define OPTION_SHIFT_D 36547
# define CONTRL_N 14
# define SHIFT_UP 71683997260571
# define SHIFT_DOWN 71683997260571
# define CONTRL_F 6
# define CONTRL_D 4
# define CONTRL_C 3
# define TAB_KEY 9
# define RETURN_KEY 10
# define DELETE_AT_POSITION 2117294875
# define BGYELLOW "\033[7;33m"
# define RESET "\033[0m"

typedef struct	s_autolist
{
	int					len;
	int					is_dic;
	int					ct;
	char				name[INPUT_MAX_LEN];
	struct s_autolist	*next;
	struct s_autolist	*pre;
}				t_autolist;

typedef struct	s_win
{
	int		max;
	int		line;
	int		col;
	int		ct_lt;
}				t_win;

typedef struct	s_line
{
	int				pos;
	unsigned char	buf[INPUT_MAX_LEN];
	unsigned char	cp[INPUT_MAX_LEN];
	unsigned char	here_mark[INPUT_MAX_LEN];
	unsigned char	here[INPUT_MAX_LEN];
	unsigned char	ici_doc[INPUT_MAX_LEN];
	unsigned char	auto_compare[INPUT_MAX_LEN];
	int				buf_len;
	int				line_max;
	int				screen_height;
	int				start_po;
	int				his_mostdown;
	int				his_mostup;
	int				up_indown;
	int				one_his;
	int				here_end;
	int				is_tabb4;
	int				auto_ct;
	int				auto_is_dic;
	int				auto_current_dic;
	t_win			w;
	t_autolist		*auto_lt;

	int				(*printable)(struct s_line *line, unsigned long a_key);
	int				(*move_left)(struct s_line *line);
	int				(*move_right)(struct s_line *line);
	int				(*delete_key)(struct s_line *line);
	int				(*move_nleft)(struct s_line *line);
	int				(*move_nright)(struct s_line *line);
	int				(*mv_left_word)(struct s_line *line);
	int				(*mv_right_word)(struct s_line *line);
	int				(*history_up)(struct s_line *line);
	int				(*history_down)(struct s_line *line);
	int				(*cp_all)(struct s_line *line);
	int				(*cp_begin)(struct s_line *line);
	int				(*cp_end)(struct s_line *line);
	int				(*cut_all)(struct s_line *line);
	int				(*cut_begin)(struct s_line *line);
	int				(*cut_end)(struct s_line *line);
	int				(*paste)(struct s_line *line);
	int				(*go_up)(struct s_line *line);
	int				(*go_down)(struct s_line *line);
	int				(*ctrl_d)(struct s_line *line);
	int				(*return_key)(struct s_line *line);
	int				(*delete_at_position)(struct s_line *line);
	int				(*my_tabkey)(struct s_line *line, char **env);
	int				(*engine)(struct s_line *line, unsigned long a_key, char **env);
}				t_line;

typedef struct	s_key
{
	unsigned long	a_key;
	int				(*func)(t_line *);
}				t_key;

typedef struct	s_helper
{
	int		i;
	int		j;
	int		k;
	int		index;
}				t_helper;

char		g_temp_file[INPUT_MAX_LEN];

int				init_attr(int mod);
int				my_putc(int c);
int				engine(t_line *line, unsigned long key, char **env);
int				move_left(t_line *line);
int				move_nleft(t_line *line);
int				mv_left_word(t_line *line);
int				mv_right_word(t_line *line);
int				move_right(t_line *line);
int				move_nright(t_line *line);
int				delete_key(t_line *line);
int				delete_all(t_line *line);
int				delete_at_position(t_line *line);
int				ctrl_d(t_line *line);
int				my_tabkey(t_line *line, char **env);
int				ctrl_c(char *new_line, t_line *line);
int				printable(t_line *line, unsigned long key);
void			put_a_key(t_line *line, unsigned long key);
int				history_up(t_line *line);
int				history_down(t_line *line);
int				cp_all(t_line *line);
int				cp_begin(t_line *line);
int				cp_end(t_line *line);
int				cut_all(t_line *line);
int				cut_begin(t_line *line);
int				cut_end(t_line *line);
int				paste(t_line *line);
int				go_up(t_line *line);
int				go_down(t_line *line);
int				return_key(t_line *line);
int				get_line(char *prompt, char *new_line, t_line *line, char **env);
void			init_line(char	*prompt, t_line *line);
int				prompt_open_quote(char *line, char **env);
char			**path(char **env);
int				dslash_before(char *line, int index);
void			ft_freestrstr(char **cp_env);
unsigned long	get_key(void);


/*
** auto_complet.c
*/
t_autolist		*add_a_list(t_autolist *list, char *name, unsigned char type);
t_autolist		*add_one_list(t_autolist *list, t_autolist *add);
int				nb_list(t_autolist *list);
void			free_auto_lt(t_line *line);
void			is_tab(unsigned long key, t_line *line);

/*
** sort_list.c
*/
void			del_one_list(t_autolist **list, t_autolist *del);
void			sort_list(t_autolist **list);

/*
** line_auto_color.c
*/
void			bg_yellow(void);
void			color_reset(void);

#endif
