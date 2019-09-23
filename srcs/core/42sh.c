/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   42sh.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 16:44:30 by arsciand          #+#    #+#             */
/*   Updated: 2019/09/23 18:37:23 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <unistd.h>

/*
**	TO_DO :
**	- signal
**	- logger ?
**	- A fonction for return value (exit_handler) Need talks about it..
*/

int		main(int ac, char **av, char **environ)
{
	t_core	shell;

	init_shell(&shell);

	/* Parse char **av and fill option */
	if (get_opt(ac, av, &shell) != SUCCESS)
		return (EXIT_FAILURE);

	/*
	**	Get t_lst *env, a linked list of char **environ with {key}
	**	and {value} format. WARNING empty char **environ not supported yet
	*/
	if (set_env(&shell, av, environ) != SUCCESS)
		return (EXIT_FAILURE);

	/* Options output */
	print_opt(&shell);

	/* DEBUG */
	print_env(&shell);

	/* Everything else will happen here */
	load_prompt(&shell);
	free_env(shell.env);
	free_hash_map(&shell.hash);			// For now here ..
	return (EXIT_SUCCESS);
}
