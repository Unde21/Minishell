#include "builtins.h"
#include "exec.h"
#include "parsing.h"
#include <stdlib.h>

bool	unset_loop(char *key, t_env *head, t_env *prev, t_data *data)
{
	if (key == NULL)
	{
		data->return_value = 1;
		data->env_array = listed_env_to_array(data, data->listed_env);
		return (print_err_false(ERR_MALLOC));
	}
	while (head)
	{
		if (ft_strcmp(head->key, key) == 0)
		{
			if (prev)
				prev->next = head->next;
			else
				*data->listed_env = *head->next;
		}
		prev = head;
		head = head->next;
	}
	return (true);
}

bool	ft_unset(t_data *data, t_env **listed_env, t_cmd *cmd)
{
	t_env	*head;
	t_env	*prev;
	int		i;
	char	*key;

	i = 0;
	free_all(data->env_array);
	while (cmd->params[++i])
	{
		prev = NULL;
		head = *listed_env;
		key = get_key(cmd->params[i]);
		unset_loop(key, head, prev, data);
	}
	data->env_array = listed_env_to_array(data, data->listed_env);
	if (data->env_array == NULL)
	{
		data->return_value = 1;
		free(key);
		return (print_err_false(ERR_MALLOC));
	}
	free(key);
	return (true);
}
