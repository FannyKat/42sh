/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh42.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 16:40:51 by arsciand          #+#    #+#             */
/*   Updated: 2019/09/23 19:13:41 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH42_H
# define SH42_H

# include "shared_libft.h"
# include "define.h"
# include "struct.h"

# include <stdlib.h>

# include <stdio.h> // /!\ For debug only !

/*
**	Core
*/

void		credit(t_core *shell);
void		init_prompt(void);
void		print_opt(t_core *shell);
void		load_prompt(t_core *shell);
void		free_env(t_lst *env);
void		free_prompt(t_core *shell, char *line);

/*
**	DB
*/

void		init_shell(t_core *shell);
int8_t		get_opt(int ac, char **av, t_core *shell);
int8_t		set_env(t_core *shell, char **argv, char **environ);
t_db		*fetch_db(t_db *db, const char *s, const u_int8_t var_type);
int8_t		get_tokens(t_core *shell, char *line);

/*
**	Exec
*/

void		exec_process(t_core *shell, t_lst *env);
void		exec_handler(t_core *shell, u_int8_t handler);
char		*get_bin(t_core *shell, t_lst *env);
char		**set_envp(t_core *shell);

/*
**	hash_map
*/
int8_t		locate_hash(t_core *shell, t_hash *hash);
int8_t		add_hash_map(t_core *shell, t_hash *hash);
int8_t		resize_hash_map(t_core *shell, t_hash *hash);
u_int32_t	get_hash(char *line, u_int32_t size);
t_db		*fetch_hash_db(t_db *db, const char *key, const char *value);
void		free_hash_map(t_hash *hash);

/*
**	DEV
*/

void		print_tokens(t_core *shell);
void		print_env(t_core *shell);
void		print_hash_map(t_hash *hash);

/*
**	===========================================================================
**	SHELL VARIABLES TOOLS......................................................
**	===========================================================================
*/

int8_t	increment_shlvl(t_core *core);
int8_t	update_pwd(t_core *core);
int8_t	update_(t_core *core);
int8_t	update_ifs(t_core *core);
int8_t	update_termsize(t_core *core);
int8_t	create_term(t_core *core);
t_db	*modify_db(t_db	*db, char *new_value, u_int8_t new_type);
t_db	*get_or_create_db(t_core *core, char *key, u_int8_t var_type);
t_db	*search_db(t_lst *env, char *key);

#endif
