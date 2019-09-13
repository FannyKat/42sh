/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guvillat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/31 15:41:31 by guvillat          #+#    #+#             */
/*   Updated: 2019/07/31 15:43:39 by guvillat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int	ft_isalpha(int c)
{
	return (((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) ? 1 : 0);
}

int	ft_isdigit(int c)
{
	return ((c >= '0' && c <= '9') ? 1 : 0);
}

//NEED ledition de ligne pour tester
void newline_lexer(t_lexer *lexer)
{
	char *buf;

	buf = NULL;
	if (!lexer->buff)
		lexer->status = END;
	else
	{
		if (lexer->buff[lexer->buf_pos] == '\n')
		{
			buf = ft_strsub(lexer->buff, lexer->buf_pos, 1);
	 		ft_add_token(&lexer->tok, TOK_NEWLINE, buf);
	 		lexer->ntok++;
	 		lexer->buf_pos++;
	 		free(buf);
		}
	}
	lexer->status = START;
}

void start_lexer(t_lexer *lexer)
{
	if (lexer->buff[lexer->buf_pos] == '\0')
		lexer->status = END;
	else if (lexer->buff[lexer->buf_pos] == ' ' || lexer->buff[lexer->buf_pos] == '\t')
	{
		lexer->io_here = 0;
		while (lexer->buff[lexer->buf_pos] == ' ' || lexer->buff[lexer->buf_pos] == '\t')
			lexer->buf_pos++;
	}
	else if (ft_strchr(OPERATORS, lexer->buff[lexer->buf_pos]))
		lexer->status = OPERATOR;
	else if (ft_isdigit(lexer->buff[lexer->buf_pos]))
		lexer->status = IO_NUMBER;
	else if (ft_strchr(&lexer->buff[lexer->buf_pos], '\n'))
		lexer->status = NEWLINE;
	else if (ft_strchr(&lexer->buff[lexer->buf_pos], '='))
		lexer->status = ASSIGNEMENT_WORD;
	else
		lexer->status = NAME;
}


//A COMPLETER
void end_lexer(t_lexer *lexer)
{
	if (lexer->buff == '\0')
		lexer->status = END;
	else
	{
		lexer->status = START;
		lexer->buf_pos++;
	}
}

void	lexer(t_core *shell, char *line)
{
	t_lexer *lexer;
	// t_parser *parser;

	if (line == NULL)
		return ;
	while (*line == '\t' || *line == ' ')
		line++;
	if (*line == '\0')
		return ;
	lexer = init_lexer(shell, line);
	while (lexer->status != END)
		lexer->lex[lexer->status](lexer);
	ft_printtoklist(lexer);
}