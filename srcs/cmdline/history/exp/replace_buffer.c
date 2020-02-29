/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_buffer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 04:02:43 by fcatusse          #+#    #+#             */
/*   Updated: 2020/02/29 14:20:24 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static void	replace_buffer(t_read *term, char *begin, char *end, char *content)
{
	char	*tmp;

	tmp = NULL;
	if (term->width - term->prompt_len == 2)
		term->buffer = ft_strdup(content);
	else if (begin && end)
	{
		tmp = ft_strjoinf(begin, content, 1);
		term->buffer = ft_strjoinf(tmp, end, 3);
	}
	else if (end)
		term->buffer = ft_strjoinf(content, end, 2);
	else if (begin)
		term->buffer = ft_strjoinf(begin, content, 1);
	else
		term->buffer = ft_strdup(content);
}

/*
**		To insert in buffer the content found from the hst lst
*/

void		insert_content(int j, int i, t_read *term, char *content)
{
	char	*begin;
	char	*end;
	int		inc_len;
	int		buff_len;

	inc_len = 0;
	end = NULL;
	begin = NULL;
	buff_len = ft_strlen(term->buffer);
	if (i >= BUFF_SIZE)
	{
		inc_len = ft_strlen(term->buffer) + ft_strlen((char *)content);
		term->buffer = ft_realloc(term->buffer, inc_len);
	}
	if (i > 0)
		begin = ft_strsub(term->buffer, 0, i);
	if (i + j < buff_len)
		end = ft_strsub(term->buffer, i + j, buff_len - (i + j));
	ft_strdel(&term->buffer);
	replace_buffer(term, begin, end, content);
}
