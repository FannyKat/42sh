/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <mpivet-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 00:24:24 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/02/13 16:56:57 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int8_t	is_a_blt(const char *cmd)
{
	static char	*blt_names[14] = {"set", "unset", "export", "exit", "cd"
	, "echo", "pwd", "type", "fg", "jobs", "bg", "hash", "fc", "test"};
	int			i;

	i = 0;
	while (i < 14)
	{
		if (ft_strcmp(blt_names[i], cmd) == 0)
			return (i);
		i++;
	}
	return (FAILURE);
}

int8_t	call_builtin(t_core *shell, t_process *process, int blt)
{
	static int8_t	(*blt_call[14])(t_core *shell, t_process *process) = {
		builtin_set, builtin_unset, builtin_export, builtin_exit, builtin_cd
		, builtin_echo, builtin_pwd, builtin_type, builtin_fg, builtin_jobs
		, builtin_bg, builtin_hash, builtin_fc, builtin_test};
	int				ret;

	exec_redirs(shell, process->redir_list);
	ret = blt_call[blt](shell, process);
	close_fds(process->redir_list);
	return (ret);
}
