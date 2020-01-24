/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_subprompt.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 15:46:03 by fcatusse          #+#    #+#             */
/*   Updated: 2020/01/24 19:52:38 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

uint8_t		goto_next_quote(char *buffer, char quote_type, int *i)
{
	while (buffer[(*i)++] != '\0')
		if (buffer[*i] == quote_type)
			return (TRUE);
	return (FALSE);
}

char		set_quote_type(char quote)
{
	if (quote == QUOTE || quote == DQUOTE || quote == BQUOTE)
		return (quote);
	else if (quote == BRACKET_OPEN)
		return (quote = BRACKET_CLOSE);
	else if (quote == CURLY_BRACKET_OPEN)
		return (quote = CURLY_BRACKET_CLOSE);
	return ('\0');
}

uint8_t		quotes_is_matching(t_read *term, char *quote)
{
	int	i;

	i = -1;
	while (term->buffer[++i])
	{
		if (term->buffer[i] == BACKSLASH)
			i += 2;
		if ((*quote = set_quote_type(term->buffer[i])) != '\0')
		{
			if (goto_next_quote(term->buffer, *quote, &i) == TRUE)
				continue ;
			else
				return (FALSE);
		}
	}
	return (TRUE);
}

uint8_t		check_subprompt(t_read *term)
{
	int		i;
	char	quote;

	i = -1;
	quote = '\0';
	if (quotes_is_matching(term, &quote) == TRUE)
		if (check_backslash(term, &quote) == FALSE)
			return (FALSE);
	if (quote != '\0')
	{
		term->sub_prompt = TRUE;
		load_subprompt(quote, term);
		return (TRUE);
	}
	return (FALSE);
}
