/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   name_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 16:15:08 by guvillat          #+#    #+#             */
/*   Updated: 2020/02/21 18:04:18 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static int		loop_till_next_quote(const char *str, int index, char quote)
{
	if (!str[index])
		return (index);
	while (str[index])
	{
		if (quote == '\"' && check_backslash_nbr((char*)str, &index))
		{
			index++;
			continue ;
		}
		if (str[index] == quote)
			break ;
		index += 1;
	}
	return (index);
}

void			check_all_quotes(char *str, int *index)
{
	int			i;

	i = *index;
	if (str[i] == '\\')
	{
		if (str[i + 1])
			i++;
	}
	else if (str[i] == '\'')
		i = loop_till_next_quote(str, i + 1, '\'');
	else if (str[i] == '`')
		i = loop_till_next_quote(str, i + 1, '`');
	else if (str[i] == '\"')
		i = loop_till_next_quote(str, i + 1, '\"');
	else if (str[i] == '{')
		i = loop_till_next_quote(str, i, '}');
	/* else if (str[i] == '(') */
	/* 	i = loop_till_next_quote(str, i, ')'); */
	*index = i;
}

int				get_word_size_ntype(int i, char *str)
{
	int		index;

	index = 0;
	if (!str || !str[i])
		return (0);
	index = i;
	while (str[index])
	{
		check_all_quotes(str, &index);
		if ((index >= 1 && str[index - 1] != '\\')
			&& ft_strchr(CHAR_INTERRUPT, str[index]))
			break ;
		index++;
	}
	return (index);
}

static t_lst	*word_lexer(t_lexer *lexer, t_lst *lexer_token)
{
	int		i;
	char	*str;

	i = lexer->buf_pos;
	str = NULL;
	if (!(i = get_word_size_ntype(i, lexer->buff)))
		return (NULL);
	if (!(str = ft_strsub(lexer->buff, lexer->buf_pos, i - lexer->buf_pos)))
		return (NULL);
	ft_lstappend(&lexer_token, ft_lstnew(
				fetch_token(&lexer->token, P_WORD, str), sizeof(t_token)));
	free(str);
	lexer->ntok++;
	lexer->buf_pos = i;
	return (lexer_token);
}

t_lst			*name_lexer(t_lexer *lexer, t_lst *lexer_token)
{
	char	*str;

	str = NULL;
	if (!lexer->buff)
	{
		lexer->status = L_END;
		return (lexer_token);
	}
	lexer_token = word_lexer(lexer, lexer_token);
	lexer->status = L_START;
	return (lexer_token);
}
