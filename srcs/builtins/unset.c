#include "builtins.h"
#include "exec.h"
#include "parsing.h"
#include <stdlib.h>

static void	unset_free(t_env *tmp)
{
	free(tmp->value);
	free(tmp->full_line);
	free(tmp->key);
	free(tmp);
}

static bool	unset_loop(char *key, t_env **head, t_env *prev, t_data *data)
{
	t_env	*tmp;
	t_env	*current;

	current = *head;
	if (key == NULL)
	{
		data->env_array = listed_env_to_array(data, data->listed_env);
		return (print_err_false(ERR_MALLOC));
	}
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			if (prev)
				prev->next = current->next;
			else
				data->listed_env = current->next;
			tmp = current;
			unset_free(tmp);
			return (true);
		}
		prev = current;
		current = current->next;
	}
	return (true);
}

static bool	reset_env_array(t_data *data)
{
	data->env_array = listed_env_to_array(data, data->listed_env);
	if (data->env_array == NULL)
	{
		data->return_value = 1;
		return (print_err_false(ERR_MALLOC));
	}
	return (true);
}

bool	ft_unset(t_data *data, t_cmd *cmd)
{
	t_env	*prev;
	int		i;
	char	*key;

	i = 0;
	if (lst_size(data->listed_env) == 1)
		return (true);
	free_all(data->env_array);
	while (cmd->params[++i])
	{
		prev = NULL;
		key = get_key(cmd->params[i]);
		if (unset_loop(key, &data->listed_env, prev, data) == false)
		{
			free(key);
			data->return_value = 1;
			return (false);
		}
		free(key);
	}
	if (reset_env_array(data) == false)
		return (false);
	return (true);
}
