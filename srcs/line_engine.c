/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_engine.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saxiao <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/27 15:47:13 by saxiao            #+#    #+#             */
/*   Updated: 2018/09/13 16:59:30 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edit.h"

static void	init_for_enginie_2(t_key *t, t_line *line)
{
	t[11].a_key = CONTRL_E;
	t[11].func = line->cp_end;
	t[12].a_key = ALT_S;
	t[12].func = line->cut_all;
	t[13].a_key = ALT_M;
	t[13].func = line->cut_begin;
	t[14].a_key = CONTRL_PERCENT;
	t[14].func = line->cut_end;
	t[15].a_key = CONTRL_P;
	t[15].func = line->paste;
	t[16].a_key = ALT_UP;
	t[16].func = line->go_up;
	t[17].a_key = ALT_DOWN;
	t[17].func = line->go_down;
	t[18].a_key = DELETE_AT_POSITION;
	t[18].func = line->delete_at_position;
	t[19].a_key = CONTRL_D;
	t[19].func = line->ctrl_d;
	t[20].a_key = RETURN_KEY;
	t[20].func = line->return_key;
}

static void	init_for_engine(t_key *t, t_line *line)
{
	t[0].a_key = ARROW_LEFT;
	t[0].func = line->move_left;
	t[1].a_key = ARROW_RIGHT;
	t[1].func = line->move_right;
	t[2].a_key = ARROW_UP;
	t[2].func = line->history_up;
	t[3].a_key = ARROW_DOWN;
	t[3].func = line->history_down;
	t[4].a_key = MY_DELECT;
	t[4].func = line->delete_key;
	t[5].a_key = MY_END;
	t[5].func = line->move_nright;
	t[6].a_key = MY_HOME;
	t[6].func = line->move_nleft;
	t[7].a_key = CONTRL_L;
	t[7].func = line->mv_left_word;
	t[8].a_key = CONTRL_H;
	t[8].func = line->mv_right_word;
	t[9].a_key = CONTRL_A;
	t[9].func = line->cp_all;
	t[10].a_key = CONTRL_B;
	t[10].func = line->cp_begin;
	init_for_enginie_2(t, line);
}

int			engine(t_line *line, unsigned long key, char **env)
{
	int		i;
	t_key	t[NB_KEY];

	i = -1;
	if ((32 <= key && key <= 126))
	{
		if (line->buf_len == INPUT_MAX_LEN - 1)
		{
			line->is_tabb4 = 0;
			g_end_line = 1;
			return (0);
		}
		line->auto_ct = -1;
		line->printable(line, key);
	}
	else if (key == TAB_KEY)
		my_tabkey(line, env);
	else
	{
		init_for_engine(t, line);
		while (++i < NB_KEY)
		{
			if (key == (t[i].a_key))
			{
				t[i].func(line);
				if (line->is_tabb4)
					
				free_auto_lt(line);
				line->auto_ct = -1;
				}
		}
	}
	is_tab(key, line);
	return (0);
}
