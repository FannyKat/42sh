/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 19:30:58 by fcatusse          #+#    #+#             */
/*   Updated: 2020/02/07 01:21:40 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int8_t			fc_error(u_int64_t opt, int err_num)
{
	if (err_num == 0)
		ft_dprintf(2, "42sh: fc: history specification out of range\n");
	else if (err_num == 1)
		print_usage("fc", opt % 128, "fc: usage: fc [-e ename] [-lnr] [first] [last] or fc -s [pat=rep] [command]");
	else if (err_num == 2)
	{
		ft_dprintf(2, "42sh: fc: -e: option requires an argument\n");
		ft_dprintf(STDERR_FILENO, "fc: usage: fc [-e ename] [-lnr] [first] [last] or fc -s [pat=rep] [command]\n");
	}
	else
		ft_dprintf(STDERR_FILENO,
				"42sh: fc: failed to open or create file: %s\n", FC_TMP_FILE);
	return (FAILURE);
}

int8_t			fc_options(char **av, u_int64_t opt)
{
	if (opt & (1ULL << 4))
	{
		while (*av)
		{
			if (ft_strequ(*av, "-e") && *(av + 1) == NULL)
				return (FALSE);
			(av)++;
		}
	}
	return (TRUE);
}

/*
**	Fix Command builtin have 2 modes :
**	Editing (default) & Listing (-lnr options)
*/

int8_t			builtin_fc(t_core *shell, t_process *process)
{
	t_lst		*w;
	u_int64_t	opt;

	opt = 0;
	if ((w = shell->term.history) == NULL)
		return (fc_error(opt, 0));
	opt = ft_get_options(ft_tablen(process->av), process->av, "elnrs0123456789");
	if (opt & (1ULL << 63))
		return (fc_error(opt, 1));
	if (fc_options(process->av, opt) == FALSE)
		return (fc_error(opt, 2));
	else if (w && (opt & (1ULL << 18)))
		return (select_specifier(shell, w, process->av));
	else if (w && (opt & (1ULL << 11)))
		listing_mode(w, process->av, opt);
	else
		return (edit_mode(shell, process, opt));
	return (SUCCESS);
}
