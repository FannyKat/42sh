/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 23:42:04 by mpivet-p          #+#    #+#             */
/*   Updated: 2019/11/26 01:12:56 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static int8_t	ft_atol(char *s, int64_t *result)
{
	size_t	i;
	int8_t	sign;
	int64_t	nb;

	i = 0;
	nb = 0;
	sign = 1;
	while (s[i] == ' ' || (s[i] >= 9 && s[i] <= 13))
		i++;
	if (s[i] != '-' && s[i] != '+' && !(s[i] >= '0' && s[i] <= '9'))
		return (FAILURE);
	if (s[i] == '+' || s[i] == '-')
		sign *= (s[i++] == '-' ? -1 : 1);
	while (s[i] >= '0' && s[i] <= '9')
	{
		if ((nb * sign  == -922337203685477580 && s[i] > '8')
			|| (nb * sign == 922337203685477580 && s[i] > '7'))
			return (FAILURE);
		nb = (nb * 10) + (s[i++] - '0');
	}
	while (s[i] == ' ')
		i++;
	if (s[i] != 0)
		return (FAILURE);
	*result = nb;
	return (SUCCESS);
}

int8_t		leave_shell(t_core *shell, int exit_value)
{

	//Call all functions to free and restore terminal

	(void)shell;
	write(STDERR_FILENO, "exit\n", 5);
	exit(exit_value);
}

int8_t			builtin_exit(t_core *shell, t_process *process)
{
	int64_t	exit_value;
	int		argc;

	argc = ft_tablen(process->av);
	exit_value = 0;
	if (argc == 1)
		leave_shell(shell, 0);
	if (ft_atol(process->av[1], &exit_value) != SUCCESS)
	{
		dprintf(STDERR_FILENO, "bash: exit: %s: numeric argument required\n"
				, process->av[1]);
		leave_shell(shell, 255);
	}
	else if (argc == 2)
		leave_shell(shell, exit_value & 0xFF);
	dprintf(STDERR_FILENO, "bash: exit: too many arguments\n");
	return (FAILURE);
}
