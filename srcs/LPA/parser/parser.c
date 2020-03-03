/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 11:47:05 by guvillat          #+#    #+#             */
/*   Updated: 2020/03/03 19:03:40 by guvillat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static void		init_start_graph(t_graph *graph)
{
	static enum e_pstate	tab_good_type[] = {P_WORD, P_GREAT, P_LESS, P_DGREAT
		, P_GREATAND, P_LESSAND, P_DLESS, P_DLESSDASH, P_ASSIGN, P_IONUMBER
		, P_START, P_ERROR};

	graph[P_START].good_type = tab_good_type;
	graph[P_NEWLINE].good_type = tab_good_type;
	graph[P_PIPE].good_type = tab_good_type;
	graph[P_ORIF].good_type = tab_good_type;
	graph[P_ANDIF].good_type = tab_good_type;
}

static t_parser	*ft_init_graph(t_parser *parser)
{
	init_start_graph(parser->graph);
	init_redirect_graph(parser->graph);
	init_process_graph(parser->graph);
	init_ionumber_graph(parser->graph);
	init_word_graph(parser->graph);
	return (parser);
}

static u_int8_t	graph(enum e_pstate *c, enum e_pstate n, enum e_pstate ps[])
{
	u_int8_t	i;

	i = 0;
	if (ps == NULL)
		return (0);
	while (ps[i] != P_ERROR)
	{
		if (n == ps[i])
		{
			*c = n;
			return (1);
		}
		i++;
	}
	return (0);
}

u_int8_t		parser(t_lst *lexer)
{
	t_parser	*parser;
	t_lst		*tok_lst;

	parser = NULL;
	if (!lexer)
		return (FALSE);
	if (!(parser = (t_parser*)malloc(sizeof(t_parser))))
		return (FALSE);
	parser->state = P_START;
	tok_lst = lexer;
	parser = ft_init_graph(parser);
	while (tok_lst)
	{
		if (!(graph(&parser->state, ((t_token*)tok_lst->content)->id,
			parser->graph[parser->state].good_type)))
		{
			ft_printf("42sh: syntax error near unexpected token `%s'\n",
				((t_token*)tok_lst->content)->data);
			free(parser);
			return (FALSE);
		}
		tok_lst = tok_lst->next;
	}
	free(parser);
	return (TRUE);
}
