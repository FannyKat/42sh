/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ac_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <fcatusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 15:13:52 by fcatusse          #+#    #+#             */
/*   Updated: 2019/10/10 15:14:45 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void			parse_env(char *prev_b, char *to_find, t_read *input)
{
	t_lst		*env;
	t_lst		*head;
	char		*tmp;

	tmp = NULL;
	env = input->shell->env;
	head = env;
	while (env)
	{
		if (isstart(((t_db *)(env->content))->key, to_find + 1))
		{
			tmp = ft_strjoin("$", ((t_db *)(env->content))->key);
			if (read_again(&prev_b, NULL, tmp, input) == FALSE)
			{
				ft_strdel(&tmp);
				return ;
			}
		}
		if (env->next)
			env = env->next;
		else
			env = head;
	}
}

/*
** 		Split all bin/sbin directories in an array
*/

char			**split_path(t_core *shell, char *str)
{
	char		**array;
	t_lst		*env;

	env = shell->env;
	array = NULL;
	while (env)
	{
		if (!ft_strcmp(str, ((t_db*)(env->content))->key))
		{
			array = ft_strsplit(((t_db*)(env->content))->value, ":");
			break ;
		}
		env = env->next;
	}
	return (array);
}
