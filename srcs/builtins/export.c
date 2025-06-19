#include "builtins.h"
#include "exec.h"
#include "parsing.h"
#include <stdlib.h>
#include <unistd.h>

static bool	export_old(t_data *data, t_env *listed_env, char *params, char *key)
{
	while (listed_env)
	{
		if (ft_strcmp(listed_env->key, key) == 0)
		{
			free(listed_env->value);
			listed_env->value = get_value(data, key);
			if (listed_env->value == NULL)
			{
				free(key);
				return (print_err_false(ERR_MALLOC));
			}
			free(listed_env->full_line);
			listed_env->full_line = ft_strdup(params);
			if (listed_env->full_line == NULL)
			{
				free(key);
				return (print_err_false(ERR_MALLOC));
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
		if (export_new(data, data->listed_env, data->cmd->params[i]) == false)
			return (false);
	}
	key = get_key(data->cmd->params[i]);
	if (key == NULL)
		return (print_err_false(ERR_MALLOC));
	if (type == 2)
	{
		if (!export_old(data, data->listed_env, data->cmd->params[i], key))
			return (false);
	}
	else if (type == 3)
		return (append_export(data, key, data->listed_env,
				data->cmd->params[i]));
	free(key);
	return (true);
}

static bool	check_key(t_data *data, int i)
{
	if (!is_key_valid(data, data->cmd->params[i]))
	{
		return (false);
	}
	return (true);
}

void	ft_export(t_data *data)
{
	int	i;
	int	type;

	i = 0;
	type = 0;
	if (data->cmd->params[1] == NULL)
		return (export_no_argument(data->listed_env));
	while (data->cmd->params[++i])
	{
		if (check_key(data, i) == false)
			break ;
		type = export_type(data, data->cmd->params[i], data->listed_env);
		if (type < 0)
			return ;
		if (export_right_type(data, i, type) == false)
		{
			data->return_value = 1;
			if (data->env_array == NULL)
				print_err_false(ERR_MALLOC);
		}
	}
}
