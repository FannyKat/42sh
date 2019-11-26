/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_backslash.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <fcatusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 15:44:01 by fcatusse          #+#    #+#             */
/*   Updated: 2019/11/26 17:09:46 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

uint8_t		charset_count(t_read *input, char charset, int i)
{
	int	count;

	count = 0;
	while (input->buffer[i])
	{
		if (input->buffer[i] == charset)
			count++;
		i++;
	}
	if (input->buffer[i - 1] != charset)
		return (FALSE);
	return (count);
}

uint8_t		check_backslash(t_read *input, char *quote)
{
	if (input->buffer[ft_strlen(input->buffer) - 1] == BACKSLASH)
	{
		if (charset_count(input, BACKSLASH, 0) % 2 != 0)
		{
			if (ft_strlen(input->buffer) > 1)
				input->buffer = ft_strjoin(input->buffer, ";");
			*quote = BACKSLASH;
			return (TRUE);
		}
	}
	return (FALSE);
}
