/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/20 15:27:52 by arsciand          #+#    #+#             */
/*   Updated: 2019/11/30 08:59:06 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

/*
**	Global variable are initialized here. We need to figure it out wich ones
**	need to be shared.
*/

void	init_shell(t_core *shell)
{
	/*
	**	t_build
	*/
	shell->build.release = BUILDR;
	shell->build.version = BUILDV;
	shell->build.patch = BUILDP + 1;
	shell->build.date = DATE;

	/*
	**	hash
	*/
	shell->hash.map = NULL;
	shell->hash.value = 0;
	shell->hash.size = HASH_SIZE;
	shell->hash.lenght = 0;

	/*	global
	**
	*/
	shell->running_process = NULL;
	shell->env = NULL;
	shell->pos_vars = NULL;
	shell->status = 0;
	shell->opt = 0;
	shell->buff = NULL;
	shell->lexer = NULL;
	shell->job_list = NULL;
	shell->assign_list = NULL;
}
