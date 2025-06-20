/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erbuffet <erbuffet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 01:29:45 by samaouch          #+#    #+#             */
/*   Updated: 2025/06/20 11:42:08 by erbuffet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "exec.h"
#include <unistd.h>

static bool	print_error_env(t_cmd *cmd)
{
	size_t	i;

	i = 0;
	if (cmd->nb_args > 1)
	{
		if (cmd->args->is_quote == true)
		{
			ft_dprintf(2, ERR_ENV);
			while (cmd->params[++i])
			{
				ft_dprintf(2, "%s", cmd->params[i]);
				if (cmd->params[i + 1] != NULL)
					ft_dprintf(2, " ");
			}
			ft_dprintf(2, ENV_TOO_MANY);
		}
		else
		{
			ft_dprintf(2, ERR_ENV);
			ft_dprintf(2, "%s’: ", cmd->params[i]);
			ft_dprintf(2, ENV_NO_FILE);
		}
		return (false);
	}
	return (true);
}

bool	ft_env(t_data *data, t_cmd *cmd)
{
	t_env	*current;

	current = data->listed_env;
	if (print_error_env(cmd) == false)
	{
		data->return_value = 127;
		return (true);
	}
	while (current != NULL)
	{
		if (ft_strchr(current->full_line, '=') != NULL)
			ft_dprintf(STDOUT_FILENO, "%s\n", current->full_line);
		current = current->next;
	}
	return (true);
}
