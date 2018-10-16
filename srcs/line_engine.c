/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_engine.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saxiao <saxiao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/27 15:47:13 by saxiao            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2018/10/15 18:05:05 by saxiao           ###   ########.fr       */
=======
/*   Updated: 2018/10/15 12:35:08 by lumenthi         ###   ########.fr       */
>>>>>>> a10a5b1a54395ac85d8f83a0557576e671c032c1
/*                                                                            */
/* ************************************************************************** */

#include "line_edit.h"

static void	init_for_enginie_2(t_key *t)
{
	t[11].a_key = CONTRL_E;
	t[11].func = cp_end;
	t[12].a_key = ALT_S;
	t[12].func = cut_all;
	t[13].a_key = ALT_M;
	t[13].func = cut_begin;
	t[14].a_key = CONTRL_PERCENT;
	t[14].func = cut_end;
	t[15].a_key = CONTRL_P;
	t[15].func = paste;
	t[16].a_key = ALT_UP;
	t[16].func = go_up;
	t[17].a_key = ALT_DOWN;
	t[17].func = go_down;
	t[18].a_key = DELETE_AT_POSITION;
	t[18].func = delete_at_position;
	t[19].a_key = CONTRL_D;
	t[19].func = ctrl_d;
	t[20].a_key = RETURN_KEY;
	t[20].func = return_key;
}

static void	init_for_engine(t_key *t)
{
	t[0].a_key = ARROW_LEFT;
	t[0].func = move_left;
	t[1].a_key = ARROW_RIGHT;
	t[1].func = move_right;
	t[2].a_key = ARROW_UP;
	t[2].func = history_up;
	t[3].a_key = ARROW_DOWN;
	t[3].func = history_down;
	t[4].a_key = MY_DELECT;
	t[4].func = delete_key;
	t[5].a_key = MY_END;
	t[5].func = move_nright;
	t[6].a_key = MY_HOME;
	t[6].func = move_nleft;
	t[7].a_key = CONTRL_L;
	t[7].func = mv_left_word;
	t[8].a_key = CONTRL_H;
	t[8].func = mv_right_word;
	t[9].a_key = CONTRL_A;
	t[9].func = cp_all;
	t[10].a_key = CONTRL_B;
	t[10].func = cp_begin;
	init_for_enginie_2(t);
}

int			key_isarrow(unsigned long key)
{
	return (key == ARROW_LEFT || key == ARROW_RIGHT || key == ARROW_UP || key == ARROW_DOWN);
}

int			engine(t_line *line, unsigned long key, t_env **env)
{
	int		i;
	t_key	t[NB_KEY];

	i = -1;
	if (ft_isprint(key))
	{
		if (line->buf_len == INPUT_MAX_LEN - 1)
		{
			line->is_tabb4 = 0;
			line->end_line = 1;
			return (0);
		}
		line->auto_ct = -1;
		printable(line, key);
	}
	else if (key == TAB_KEY)
		my_tabkey(line, env);
	else if (line->is_tabb4 && line->auto_ct >= 0 && key_isarrow(key))
		arrow_keys_in_autoline(line, env, key);
	else
	{
		init_for_engine(t);
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
