/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guvillat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 11:45:53 by guvillat          #+#    #+#             */
/*   Updated: 2019/09/19 11:45:57 by guvillat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

/*
** In the shell command language, a word consisting solely of underscores, digits, and alphabetics
** The first character of a name is not a digit.
*/

static	int isvalid_assignement_word(char *str, size_t index)
{
	int i;

	i = index;
	if (!str || ft_isdigit(str[0]) || str[0] == '=')
		return (0);
	while (str[i] != '=')
	{
		if (str[i] == '_' || ft_isdigit(str[i]) || ft_isalpha(str[i]))
			i++;
		else
			return (0);
	}
	if (str[i + 1] && str[i + 1] == '=')
		return (0);
	return (i + 1);
}

/*
** STATE CREANT LES TOKEN ASSIGN
*/

static t_lst *create_assign_token(t_lexer *lexer, int len, t_lst *lexer_token)
{
	char *str;

	str = NULL;
	if (!(str = ft_strsub(lexer->buff, lexer->buf_pos, len - lexer->buf_pos)))
		return (lexer_token);
	if (!(ft_lstappend(&lexer_token, ft_lstnew(fetch_lexer_token(&lexer->token ,P_ASSIGN, str), sizeof(t_token)))))
		return (lexer_token);
	free(str);
	lexer->ntok++;
	lexer->buf_pos = len;
	return (lexer_token);
}

t_lst		*assignement_word_lexer(t_lexer *lexer, t_lst *lexer_token)
{
	int i;

	i = 0;
	if (!lexer->buff)
		lexer->status = L_END;
	else
	{
		if ((i = isvalid_assignement_word(lexer->buff, lexer->buf_pos)))
			lexer_token = create_assign_token(lexer, i, lexer_token);
		else
			lexer_token = name_lexer(lexer, lexer_token);
	}
	lexer->status = L_START;
	return(lexer_token);
}
