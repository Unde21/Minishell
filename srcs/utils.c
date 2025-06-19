/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samaouch <samaouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 01:34:14 by samaouch          #+#    #+#             */
/*   Updated: 2025/06/20 01:34:15 by samaouch         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <unistd.h>

bool	print_err_false(char *str_error)
{
	ft_dprintf(STDERR_FILENO, "%s", str_error);
	return (false);
}

char	*print_err_null(char *str_error)
{
	ft_dprintf(STDERR_FILENO, "%s", str_error);
	return (NULL);
}

void	reset_g_return_value(t_data *data)
{
	if (g_return_value != 0)
	{
		data->return_value = g_return_value;
		g_return_value = 0;
	}
}

void	print_ambiguous(char *s)
{
	ft_dprintf(STDERR_FILENO, "%s %s: %s", PRINT_ERR, s, ERR_AMBIGUOUS);
}
