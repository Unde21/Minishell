/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erbuffet <erbuffet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 01:29:51 by samaouch          #+#    #+#             */
/*   Updated: 2025/06/20 11:54:17 by erbuffet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "exec.h"
#include "parsing.h"
#include <stdlib.h>
#include <unistd.h>

int	lst_size(t_env *head)
{
	int		count;
	t_env	*current;

	count = 0;
	current = head;
	while (current)
	{
		count++;
		current = current->next;
	}
	return (count);
}

bool	is_key_valid(t_data *data, char *params)
{
	int	i;

	i = 0;
	if (!params || !(ft_isalpha(params[0]) || params[0] == '_'))
	{
		data->return_value = 1;
		ft_dprintf(2, "%s`%s'%s", PRT_EX, data->cmd->params[i], ERR_EXP);
		return (false);
	}
	while (params[i])
	{
		if (params[i] == '=' || (params[i] == '+' && params[i + 1] == '='))
			break ;
		if (!ft_isalnum(params[i]) && params[i] != '_')
		{
			data->return_value = 1;
			ft_dprintf(STDERR_FILENO, "error: export: `%s'%s",
				data->cmd->params[i], ERR_EXP);
			return (false);
		}
		++i;
	}
	if (params[i] == '\0')
		return (false);
	return (true);
}

int	export_type(t_data *data, char *params, t_env *listed_env)
{
	char	*key;

	key = get_key(params);
	if (!key)
	{
		print_err_false(ERR_MALLOC);
		data->return_value = 1;
		return (-1);
	}
	while (listed_env)
	{
		if (ft_strcmp(key, listed_env->key) == 0)
		{
			free(key);
			return (2);
		}
		if (ft_strnstr(params, "+=", ft_strlen(key) + 2) != NULL)
		{
			free(key);
			return (3);
		}
		listed_env = listed_env->next;
	}
	free(key);
	return (1);
}

bool	free_key_and_return_false(char *key, char *value)
{
	free(key);
	free(value);
	return (print_err_false(ERR_MALLOC));
}

void	print_export(t_env *min)
{
	if (strchr(min->full_line, '=') != NULL)
		ft_dprintf(STDOUT_FILENO, "export %s=\"%s\" \n", min->key, min->value);
	else
		ft_dprintf(STDOUT_FILENO, "export %s\n", min->full_line);
}
