/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_history.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <fcatusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 14:36:33 by fcatusse          #+#    #+#             */
/*   Updated: 2019/09/11 11:24:54 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "sh42.h"

/*
**	Open ".history" file to write history datas at the end of file
*/

void			write_history(t_read *line)
{
	int			fd;
	t_lst		*hst;

	hst = line->history;
	if (!hst)
		return ;
	if ((fd = open(HISTORY_FILE, MODE_WRITE, S_USR_RW | S_GRP_OTH_R)) == -1)
		dprintf(STDIN_FILENO, "can't open history file\n");
	while (hst->next)
		hst = hst->next;
	while (hst)
	{
		if (write(fd, hst->data, ft_strlen(hst->data)) == FAILURE
			|| write(fd, "\n", 1) == FAILURE)
		{
			dprintf(2, "write failure\n");
			close(fd);
			return ;
		}
		hst = hst->prev;
	}
	close(fd);
}

/*
**	Save the last line inserted in history list
**	Next ptr to the last line saved
*/

void			save_history(t_read *term)
{
	t_lst		*saved;

	saved = NULL;
	if (ft_strcmp(term->buffer, ""))
	{
		saved = ft_memalloc(sizeof(*saved));
		saved->prev = NULL;
		saved->next = term->history;
		saved->data = ft_strdup(term->buffer);
		if (term->history)
			term->history->prev = saved;
		term->history = saved;
		term->history_index = NULL;
	}
}

/*
**	Init history list -> load datas from history file
*/

void			init_history(t_read *term)
{
	char		*line;
	int			fd;
	uint8_t		i;

	i = -1;
	line = NULL;
	if ((fd = open(HISTORY_FILE, O_RDONLY, S_IRUSR | S_IRGRP | S_IROTH)) == -1)
		return ;
	while (ft_getnextline(fd, &line) > 0)
	{
		while (++i < ft_strlen(line))
			term->buffer[i] = line[i];
		save_history(term);
		free(line);
		ft_bzero(term->buffer, ft_strlen(term->buffer));
		i = -1;
	}
	close(fd);
}
