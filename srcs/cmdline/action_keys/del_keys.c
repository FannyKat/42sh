/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_keys.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <mpivet-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 14:37:09 by fcatusse          #+#    #+#             */
/*   Updated: 2020/03/04 21:39:15 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

/*
**	Termcaps capabilities:
**	- `del' => Delete one char position at the cursor
**	- `clr_lines' => clear the line the cursor is on, and following lines
**	- `reset_cr' => restore the cursor position
**	- `save_cr' => save cursor position
*/

static void	clear_all_lines(t_read *term)
{
	xtputs(term->tcaps[DEL_CR], 1, my_outc);
	xtputs(term->tcaps[SAVE_CR], 1, my_outc);
	xtputs(term->tcaps[CLR_LINES], 1, my_outc);
	xtputs(term->tcaps[RESTORE_CR], 1, my_outc);
	goto_prompt(term);
}

void		del_key(t_read *term)
{
	ssize_t	i;
	ssize_t	x;
	ssize_t	y;
	ssize_t	w;

	if (*term->buffer && term->x >= term->prompt_len * (term->y == 0 ? 1 : 0)
		&& term->x < term->width)
	{
		i = term->x_index - term->prompt_len - 1;
		while (term->buffer[++i])
			term->buffer[i] = term->buffer[i + 1];
		x = term->x;
		i = term->x_index;
		y = term->y;
		w = term->width - 1;
		clear_all_lines(term);
		ft_putstr_fd(term->buffer, STDERR_FILENO);
		term->x = x;
		term->x_index = i;
		term->y = y;
		term->width = w;
		xtputs(term->tcaps[RESTORE_CR], 1, my_outc);
	}
}

/*
**	Backspace key function move the cursor one char on the left
**	Call del_key function to delete char from cursor position
*/

void		bs_key(const char *buf, t_read *term)
{
	if ((term->y > 0 && term->x >= 0) || term->x > term->prompt_len)
	{
		move_left(buf, term);
		del_key(term);
	}
}
