/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <mpivet-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 16:44:30 by arsciand          #+#    #+#             */
/*   Updated: 2020/02/18 00:09:18 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <unistd.h>
#include <signal.h>

int		main(int ac, char **av, char **environ)
{
	t_core	shell;

	ft_bzero(&shell, sizeof(t_core));
	if (read(STDIN_FILENO, NULL, 0) < 0
		|| init_shell(&shell, av, environ) != SUCCESS)
		return (0);
//	if (setjmp(g_exit_leaks))
//	{
//		dprintf(STDOUT_FILENO, "Exited with free handling ..\n");
//		return (EXIT_SUCCESS);
//	}
//	else
//	{
		get_opt(ac, av, &shell);
//		dprintf(STDERR_FILENO, "Entering 42sh with setjmp activated !!!\n");
		if (shell.is_interactive)
			load_i_mode(&shell);
		else
			load_noi_mode(&shell);
//	}
	free_shell(&shell);
//	dprintf(STDERR_FILENO, "%sEXIT_SUCCESS%s\n", C_G, C_X);
	return (shell.status);
}
