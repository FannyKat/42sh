/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sigint.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <mpivet-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 16:45:16 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/02/29 14:33:06 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <signal.h>

static void		erase_line(t_core *shell)
{
	if (shell->term.status == CMD_PROMPT)
	{
		goto_prompt(&shell->term);
		ft_strdel(&shell->term.buffer);
		ft_strdel(&shell->term.tmp_buff);
		shell->term.buffer = ft_memalloc(BUFF_SIZE);
	}
	else if (shell->term.status == CMD_SUBPROMPT)
	{
		if (shell->heredoc)
			shell->heredoc = 0;
		ft_strdel(&shell->term.buffer);
		shell->term.buffer = ft_strdup(shell->term.tmp_buff);
		save_history(&shell->term);
		ft_strdel(&shell->term.buffer);
		shell->term.buffer = ft_memalloc(BUFF_SIZE);
		shell->term.status = CMD_PROMPT;
		ft_strdel(&shell->term.prompt);
		get_prompt_value(shell, "PS1");
		display_prompt(&(shell->term));
		shell->job_list = NULL;
	}
}

void			sigint_handler(int signum)
{
	t_core	*shell;

	shell = get_core(NULL);
	signal(SIGINT, sigint_handler);
	shell->status = 128 + signum;
	write(STDERR_FILENO, "\n", 1);
	update_exit_status(shell);
	erase_line(shell);
}
