/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_vars.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 16:51:00 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/02/06 22:37:04 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

/*
**	Update or create $$ special variable, containing the pid of the program
**		- Should only be executed at shell startup
*/

int8_t	update_process_id(t_core *shell)
{
	pid_t	pid;
	char	*value;
	t_db	*db;

	db = NULL;
	value = NULL;
	pid = -1;
	if (shell && (db = get_or_create_db(shell, "$", SPECIAL_VAR)) != NULL)
	{
		if ((pid = getpid()) >= 0)
			value = ft_itoa((int)pid);
		if (value && modify_db(db, value, 0) != NULL)
			return (SUCCESS);
		ft_strdel(&value);
	}
	return (FAILURE);
}

/*
**	Update the $! special variable containing the pid of the last process
**	placed in background in $! special var
**		- Should be updated each time it changes
*/

/*
int8_t	update_backgroud_pid(t_core *shell)
{
	char		*value;
	t_db		*db;
	t_process_var *ptr;

	db = NULL;
	value = NULL;
	ptr = get_last_job(shell);
	if (shell && ptr && (db = get_or_create_db(shell, "!", SPECIAL_VAR)))
	{
		value = ft_itoa((int)ptr->pid);
		if (value && modify_db(db, value, 0) != NULL)
			return (SUCCESS);
		ft_strdel(&value);
	}
	return (FAILURE);
}*/
