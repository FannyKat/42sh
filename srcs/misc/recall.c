/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recall.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 01:37:25 by mpivet-p          #+#    #+#             */
/*   Updated: 2019/11/21 22:13:21 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

t_core	*get_core(t_core *core)
{
	static t_core	*mem = NULL;

	if (core != NULL && mem == NULL)
		mem = core;
	return (mem);
}
