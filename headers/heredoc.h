/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 15:47:16 by acauchy           #+#    #+#             */
/*   Updated: 2018/11/09 17:01:20 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** heredoc_db.c
*/

void	init_heredoc_fds(void);
int		register_heredoc_fd(int fd);
void	clear_heredocs_fds(void);

/*
** heredoc.c
*/

int		apply_heredocs(t_word *wordlist, char **errmsg);
