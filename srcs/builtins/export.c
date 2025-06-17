#include "builtins.h"
#include "exec.h"
#include "minishell.h"
#include "parsing.h"
#include <stdlib.h>
#include <unistd.h>

static bool	export_new(t_env *listed_env, char *params)
{
	t_env	*new_node;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (print_err(ERR_MALLOC));
	else
	{
		new_node->key = get_key(params); // Leak si MALLOC == NULL
		if (new_node->key == NULL)
			return (false);
		new_node->value = get_value(params); // Leak si MALLOC == NULL
		if (new_node->value == NULL)
			return (print_err(ERR_MALLOC));
		new_node->full_line = ft_strdup(params); // Leak si MALLOC == NULL
		if (new_node->full_line == NULL)
			return (print_err(ERR_MALLOC));
		new_node->printed = 0;
		new_node->next = NULL;
	}
	add_back(new_node, &listed_env);
	return (true);
}

static bool	export_old(t_env *listed_env, char *params, char *key)
{
	key = get_key(params);
	if (key == NULL)
		return (false);
	while (listed_env)
	{
		if (ft_strcmp(listed_env->key, key) == 0)
		{
			listed_env->value = get_value(key); // Leak si MALLOC == NULL
			if (listed_env->value == NULL)
			{
				free(key);
				return (print_err(ERR_MALLOC));
			}
			listed_env->full_line = ft_strdup(params); // Leak si MALLOC == NULL
			if (listed_env->full_line == NULL)
			{
				free(key);
				return (print_err(ERR_MALLOC));
			}
		}
		listed_env = listed_env->next;
	}
	free(key);
	return (true);
}

static void	export_no_argument(t_env *listed_env)
{
	int		printed_count;
	int		total;
	t_env	*head;
	t_env	*min;

	printed_count = 0;
	total = lst_size(listed_env);
	while (printed_count++ < total)
	{
		head = listed_env;
		min = NULL;
		while (head)
		{
			if (!head->printed && (!min || strcmp(head->key, min->key) < 0))
				min = head;
			head = head->next;
		}
		if (min)
		{
			ft_dprintf(STDOUT_FILENO, "export %s \n", min->full_line);
			min->printed = 1;
		}
	}
	reset(listed_env);
}

static bool	export_right_type(t_data *data, int i, int type)
{
	char	*key;

	key = NULL;
	if (type == 1)
	{
		if (export_new(data->listed_env, data->cmd->params[i]) == false)
			return (false);
	}
	else if (type == 2)
	{
		if (export_old(data->listed_env, data->cmd->params[i], key) == false)
			return (false);
	}
	else if (type == 3)
	{
		if (append_export(data->listed_env, data->cmd->params[i]) == false)
			return (false);
	}
	return (true);
}

bool	ft_export(t_data *data)
{
	int	i;
	int	type;

	i = 0;
	type = 0;
	if (data->cmd->params[1] == NULL)
		export_no_argument(data->listed_env);
	while (data->cmd->params[++i])
	{
		if (!is_key_valid(data->cmd->params[i]))
		{
			ft_dprintf(STDERR_FILENO, "bash: export: `%s'",
				data->cmd->params[i]);
			ft_dprintf(STDERR_FILENO, ERR_EXPORT);
			data->return_value = 1;
			continue ;
		}
		type = export_type(data->cmd->params[i], data->listed_env);
		if (export_right_type(data, i, type) == false)
		{
			data->return_value = 1; // surement des trucs a free ici avant
			free_all(data->env_array);
			data->env_array = listed_env_to_array(data, data->listed_env);
			return (true);
		}
	}
	return (true);
}
