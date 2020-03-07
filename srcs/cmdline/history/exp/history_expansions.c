/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_expansions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 13:59:34 by fcatusse          #+#    #+#             */
/*   Updated: 2020/03/07 20:37:50 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "sh42.h"

/*
**		"!word" expansion search the word to find from the end of hst lst
*/

int64_t	call_word(t_read *term, ssize_t i)
{
	t_lst	*w;
	char	word[BUFF_SIZE];
	ssize_t	n;
	size_t	j;

	ft_bzero(word, BUFF_SIZE);
	j = 0;
	w = term->history;
	n = i + 1;
	while (n < (ssize_t)ft_strlen(term->buffer) && !ft_isblank(term->buffer[n]))
	{
		word[j] = term->buffer[n];
		n++;
		j++;
	}
	word[j + 1] = '\0';
	if (!w || n > (ssize_t)ft_lstlen(w) || n > HIST_SIZE)
		return (FAILURE);
	while (w->next && ft_isstart((char *)w->content, word) == FALSE)
		w = w->next;
	if (!w->next)
		return (FAILURE);
	insert_content(j + 2, i, term, (char *)w->content);
	return (i + ft_strlen((char *)w->content) - 1);
}

/*
**		"!-number" expansion search from the end of hst lst
*/

int64_t	callback_number(t_read *term, ssize_t i)
{
	t_lst	*w;
	char	nb[BUFF_SIZE];
	ssize_t	n;
	size_t	j;

	j = 0;
	w = term->history;
	n = i + 2;
	ft_bzero(nb, BUFF_SIZE);
	while (ft_isdigit(term->buffer[n]))
	{
		nb[j] = term->buffer[n];
		n++;
		j++;
	}
	n = ft_atoi(nb);
	if (!w || n > (ssize_t)ft_lstlen(w) || n > HIST_SIZE || n < 0)
		return (FAILURE);
	while (w && n != 0 && --n)
	{
		if (w->next)
			w = w->next;
	}
	insert_content(j + 3, i, term, (char *)w->content);
	return (i + j + 1);
}

/*
**		"!number" expansion search from the beggining of hst lst
*/

int64_t	call_number(t_read *term, ssize_t i)
{
	t_lst	*w;
	char	nb[BUFF_SIZE];
	ssize_t	n;
	size_t	j;

	j = 0;
	w = term->history;
	n = i + 1;
	ft_bzero(nb, BUFF_SIZE);
	while (ft_isdigit(term->buffer[n]))
	{
		nb[j] = term->buffer[n];
		n++;
		j++;
	}
	n = ft_atoi(nb);
	if (!w || n > (ssize_t)ft_lstlen(w) || n > HIST_SIZE || n < 0)
		return (FAILURE);
	while (w->next)
		w = w->next;
	while (w && n != 0 && --n)
		if (w->prev)
			w = w->prev;
	insert_content(j + 2, i, term, (char *)w->content);
	return (i + j + 1);
}

/*
**		"!!" expansion search the last occurence of hst list
*/

int64_t	last_cmd_back(t_read *term, ssize_t i)
{
	t_lst	*w;
	ssize_t	len;

	len = 0;
	w = term->history;
	if (!term->history || ft_strlen(term->buffer) > BUFF_SIZE)
		return (FAILURE);
	if (w && w->content)
		insert_content(2, i, term, (char *)w->content);
	len = i + (ssize_t)ft_strlen((char *)w->content);
	return (len - 1);
}
