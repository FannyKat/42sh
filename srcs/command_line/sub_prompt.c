/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <fcatusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 17:07:08 by fcatusse          #+#    #+#             */
/*   Updated: 2019/11/27 00:01:39 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

uint8_t		newline_count(char *buffer)
{
	int	i = -1;
	uint8_t	new_line;

	new_line = 0;
	while (buffer[++i])
	{
		if (buffer[i] == NEW_LINE)
			new_line++;
	}
	return (new_line);
}

void		insert_newline_in_buff(t_read *line)
{
	int		buff_index;

	buff_index = line->x_index - line->prompt_len;
	line->buffer[buff_index] = NEW_LINE;
	line->width++;
	line->x = 0;
	line->y++;
	line->x_index++;
}

uint8_t		is_eof(char buff, char quote)
{
	if (buff == QUOTE && quote == QUOTE)
		return (TRUE);
	else if (buff == DQUOTE && quote == DQUOTE)
		return (TRUE);
	else if (buff == BQUOTE && quote == BQUOTE)
		return (TRUE);
	return (FALSE);
}

void		display_subprompt(t_read *term, char quote)
{
	if (term->prompt)
		free(term->prompt);
	if (quote == DQUOTE)
		term->prompt = ft_strdup("dquote> ");
	else
		term->prompt = ft_strdup("> ");
//	term->prompt_len = ft_strlen(term->prompt);
	term->x = term->prompt_len;
	term->y = 0;
	if (get_size(term) != SUCCESS)
		exit(1);
//	ft_putstr(term->prompt);
	(quote == DQUOTE) ? ft_putstr("dquote> ") : ft_putstr("> ");
}

void		load_subprompt(char quote, t_read *line)
{
	char	buff[READ_SIZE + 1];

	line->new_line = 0;
	line->sub_prompt = 0;
	insert_newline_in_buff(line);
	ft_bzero(buff, READ_SIZE + 1);
	while (TRUE)
	{
		display_subprompt(line, quote);
	//	(quote == DQUOTE) ? ft_putstr("dquote> ") : ft_putstr("> ");
		while (xread(STDIN_FILENO, buff, READ_SIZE) > 0)
		{
			if (is_eof(buff[0], quote) == TRUE)
				line->new_line = 1;
			if (check_caps(buff, line) == TRUE)
				continue ;
			else
			{
				line->sub_prompt++;
				// insert_newline_in_buff(line);
				break ;
			}
		}
		if (line->new_line == 1)
		{
			line->sub_prompt = FALSE;
			return ;
		}
	}
}
