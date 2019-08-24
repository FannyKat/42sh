/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <fcatusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 17:07:08 by fcatusse          #+#    #+#             */
/*   Updated: 2019/08/24 12:05:56 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

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
	term = get_size(term);
//	ft_putstr(term->prompt);
	(quote == DQUOTE) ? ft_putstr("dquote> ") : ft_putstr("> ");
}

void		load_subprompt(char quote, t_read *line)
{
	char	buff[READ_SIZE];

	line->new_line = 0;
	insert_newline_in_buff(line);
	ft_bzero(buff, READ_SIZE);
	while (TRUE)
	{
		display_subprompt(line, quote);
	//	(quote == DQUOTE) ? ft_putstr("dquote> ") : ft_putstr("> ");
		while (read(STDIN_FILENO, buff, READ_SIZE))
		{
			if (is_eof(buff[0], quote) == TRUE)
				line->new_line = 1;
			if (check_caps(buff, line) == TRUE)
				continue ;
			else
			{
				insert_newline_in_buff(line);
				break ;
			}
		}
		if (line->new_line == 1)
			return ;
	}
}
