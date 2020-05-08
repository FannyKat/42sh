/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_format.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 15:29:12 by guvillat          #+#    #+#             */
/*   Updated: 2020/04/23 16:56:52 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <unistd.h>

static void	format_value(char **tablo, t_core *shell, char *value)
{
	if (tablo[1][1] == '$')
		value = exp_param(&tablo[1][1], shell);
	else if (tablo[1][1] == '~')
		value = exp_tilde(&tablo[1][1], shell);
	else
		value = ft_strdup(&tablo[1][1]);
	ft_dprintf(STDERR_FILENO, "42sh: %s: %s\n", tablo[0], value);
	ft_strdel(&value);
}

char		*questionmark_format(char **tablo, t_core *shell)
{
	char	*value;

	value = check_env_key(tablo[0], shell);
	if (value && *value != '\0')
	{
		ft_tabfree(tablo);
		return (ft_strdup(value));
	}
	else if (!tablo[1][1] && (!value || !*value))
		ft_dprintf(STDERR_FILENO,
			"42sh : %s parameter null or not set\n", tablo[0]);
	else
		format_value(tablo, shell, value);
	shell->status = 2;
	ft_tabfree(tablo);
	return (NULL);
}

char		*dash_format(char **tablo, t_core *shell)
{
	char	*value;
	size_t	i;

	i = 1;
	value = NULL;
	if ((value = check_env_key(tablo[0], shell)))
	{
		ft_tabfree(tablo);
		return (ft_strdup(value));
	}
	if (tablo[1])
	{
		if (tablo[1][1] == '$')
			value = exp_param(&tablo[1][1], shell);
		else if (tablo[1][1] == '~')
			value = exp_tilde(&tablo[1][1], shell);
		else
			value = ft_strdup(&tablo[1][1]);
	}
	ft_tabfree(tablo);
	return (value);
}

char		*length_format(char *str, t_core *shell)
{
	t_db	*db_tmp;

	db_tmp = NULL;
	if (ft_strchr(str, ':') || ft_strchr(str, '%') || ft_strchr(&str[1], '#')
		|| str[2] == '~')
	{
		ft_dprintf(STDERR_FILENO, "42sh: %s : bad substitution\n", str);
		ft_strdel(&str);
		shell->status = 2;
		shell->subst_error = 1;
		return (NULL);
	}
	if ((db_tmp = search_db(shell->env, &str[1])))
	{
		ft_strdel(&str);
		return (ft_itoa((int32_t)ft_strlen(db_tmp->value)));
	}
	ft_strdel(&str);
	return (ft_strdup("0"));
}

char		*plus_format(char **tablo, t_core *shell)
{
	char	*value;

	value = NULL;
	if ((check_env_key(tablo[0], shell)))
	{
		if (tablo[1][1] == '$')
			value = exp_param(&tablo[1][1], shell);
		else if (tablo[1][1] == '~')
			value = exp_tilde(&tablo[1][1], shell);
		else
			value = ft_strdup(&tablo[1][1]);
		ft_tabfree(tablo);
		return (value);
	}
	ft_tabfree(tablo);
	return (NULL);
}
