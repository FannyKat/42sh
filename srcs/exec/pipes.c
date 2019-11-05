/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 11:06:48 by mpivet-p          #+#    #+#             */
/*   Updated: 2019/11/05 02:45:35 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static int32_t	get_pipeline_len(t_lst *process)
{
	int i;

	i = 0;
	while (process != NULL && ((t_process*)process->content)->type == P_PIPE)
		i++;
	return (i);
}

static int8_t	pipeline_start(t_core *shell, t_lst **process, int *pipes)
{
	pid_t	pid;

	(void)shell;
	if ((pid = fork()) == 0)
	{
		if (dup2(pipes[1], 1) < 0)
		{
			dprintf(STDERR_FILENO, "42sh: dup2 error.\n");
			exit(1);
		}
		close(pipes[0]);
		close(pipes[1]);
		exec_piped_process(shell, process);
	}
	process = process->next;
	return ((pid < 0) ? FAILURE : SUCCESS);
}

void	redir_and_close(t_lst *process, int *pipes)
{
	if (dup2(pipes[0], 0) < 0
		|| (*((t_process*)process->content)->type == P_PIPE
			&& dup2(pipes[3], 1) < 0))
	{
		dprintf(STDERR_FILENO, "42sh: dup2 error.\n");
		exit(-1);
	}
	close(pipes[0]);
	close(pipes[2]);
	close(pipes[3]);
}

int8_t	pipeline_fork_error(int *pipes)
{
	close(pipes[2]);
	close(pipes[3]);
	dprintf(STDERR_FILENO, "42sh: fork error.\n");
	return (FAILURE);
}

static int8_t	pipeline_loop(t_core *shell, t_lst **process, int *pipes)
{
	pid_t	pid;

	close(pipes[1]);
	if (pipe(pipes + 2) < 0)
	{
		close(pipes[0]);
		dprintf(STDERR_FILENO, "42sh: pipe error.\n");
		return (FAILURE);
	}
	if ((pid = fork()) == 0)
	{
		redir_and_close(*process, pipes);
		exec_piped_process(shell, process);
	}
	close(pipes[0]);
	if (pid < 0)
		return(pipeline_fork_error(pipes));
	if (*((t_process*)process->content)->type == P_PIPE)
	{
		if (pipeline_loop(shell, &(*process->next), pipes + 2) != SUCCESS)
			return (FAILURE);
	}
	return (SUCCESS);
}

int8_t	exec_pipeline(t_core *shell, t_lst **process)
{
	int		*pipes;
	int		p_len;
	int		ret;

	ret = SUCCESS;
	p_len = get_pipeline_len(process);
	if ((pipes = (int*)malloc(sizeof(int) * (2 * p_len))) == NULL)
		return (FAILURE);
	if (pipeline_start(shell, process, pipes) != SUCCESS
		|| pipeline_loop(shell, process, pipes) != SUCCESS)
		ret = FAILURE;
	while (p_len--)
		wait(&(shell->status));
	free(pipes);
	return (ret);
}
