/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_edit.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saxiao <saxiao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/29 00:15:00 by saxiao            #+#    #+#             */
/*   Updated: 2018/11/14 11:48:03 by saxiao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LINE_EDIT_H
# define LINE_EDIT_H

# include <sys/types.h>
# include <limits.h>
# include "libft.h"
# include "utils.h"
# include "env.h"

# define ADVANCED_LINE_EDIT 1
# define BASIC_LINE_EDIT 0
# define NB_KEY 22
# define NORMAL_PROMPT 1
# define HEREDOC_PROMPT 2
# define SQUOTE_PROMPT 3
# define DQUOTE_PROMPT 4
# define SLASH_PROMPT 5

# define ARROW_LEFT 4479771
# define ARROW_RIGHT 4414235
# define ARROW_UP 4283163
# define ARROW_DOWN 4348699
# define MY_DELECT 127
# define MY_HOME 4741915
# define MY_END 4610843
# define CT_SHIFT_ARROW_LEFT 74999712013083
# define CT_SHIFT_ARROW_RIGHT 73900200385307
# define CONTRL_L 12
# define OPTION_SHIFT_A 34243
# define OPTION_SHIFT_B 45508
# define OPTION_SHIFT_E 46274
# define CONTRL_P 16
# define OPTION_A 42435
# define OPTION_B 11241698
# define OPTION_E 46274
# define OPTION_SHIFT_U 43202
# define OPTION_SHIFT_D 36547
# define OPTION_ARROW_UP 1096489755
# define OPTION_ARROW_DOWN 1113266971
# define CONTRL_F 6
# define CONTRL_D 4
# define CONTRL_C 3
# define TAB_KEY 9
# define RETURN_KEY 10
# define DELETE_AT_POSITION 2117294875

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
	char			prompt[INPUT_MAX_LEN];
	int				buf_len;
	int				real_nb_auto_line;
	int				line_max;
	int				screen_height;
	int				start_po;
	int				his_mostdown;
	int				his_mostup;
	int				up_indown;
	int				one_his;
	int				here_end;
	int				is_tabb4;
	int				auto_last_choice_len;
	int				auto_ct;
	int				auto_is_dic;
	int				auto_current_dic;
	int				is_special_prompt;
	int				end_line;
	int				clc;
	int				dld;
	t_win			w;
	t_autolist		*auto_lt;
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

void			init_attr(int mod);
int				my_putc(int c);
int				engine(t_line *line, unsigned long key, t_env **env);
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
int				top_round(int nb, int dev);
int				get_line(char *pt, char *new_line, t_line *line, t_env **env);
void			init_line(char	*prompt, t_line *line);
char			**path(t_env **env);
int				dslash_before(char *line, int index);
void			ft_freestrstr(char **cp_env);
unsigned long	get_key(void);
void			init_for_engine(t_key *t);

/*
** auto_my_tabkey.c
*/

int				my_tabkey(t_line *line, t_env **env);
void			cusor_back(t_line *line);
int				nb_line_command(t_line *line);

/*
** sort_list.c
*/
void			del_one_list(t_autolist **list, t_autolist *del);
void			sort_list(t_autolist **list);

/*
** line_auto_color.c
*/
void			bg_yellow(void);
void			boldgreen(void);
void			blue(void);
void			color_reset(void);

/*
** line_input.c
*/

char			*ask_for_input(int prompt_choice, char *ctrl);

/*
** auto_key_isarrow.c
*/

int				key_isarrow(unsigned long key);
int				arrow_keys_in_autoline(t_line *l, t_env **ev, unsigned long k);

/*
** auto_start_current.c
*/

int				auto_start(char *line);
int				auto_current(t_line *line);

/*
** auto_add_a_list_nbuildin.c
*/

t_autolist		*add_a_list(t_autolist *list, char *name, unsigned char type);
t_autolist		*add_one_list(t_autolist *list, t_autolist *add);
t_autolist		*addlist_buildin_alias(t_line *line, t_autolist *list);

/*
** auto_get_autolist.c
*/

t_autolist		*get_autolist(t_line *line, t_env **env);
void			path_last_slash(char *start, char *dic, int index);

/*
** auto_put_colum.c
*/

void			put_colum(t_line *line);

/*
** auto_calcu.c
*/

void			init_win(t_autolist *list, int win_col, t_win *win);
int				nb_list(t_autolist *list);
void			free_auto_lt(t_line *line);
void			is_tab(unsigned long key, t_line *line);

/*
** auto_return_key.c
*/

int				return_key(t_line *line);
void			clear_auto_onscreen(t_line *line);
void			put_choice_end(t_line *line, int chioce_isdic);

/*
** auto_put_choice.c
*/

void			one_autolist(t_line *line);
void			put_choice(t_line *line, int *i);

/*
** line_clsreen_winchangesize.c
*/

void			print_prompt(char *prompt);
int				my_clear_screen(t_line *line);
int				winsize_change(t_line *line);

/*
** auto_put_colum.c
*/

int				newline_b4(t_line *line, int index);

/*
** auto_help.c
*/

int				last_letter_not_last_col(t_line *line);
void			for_put_a_key(t_line *line, unsigned long key);
int				not_last_letter(t_line *line);

#endif
