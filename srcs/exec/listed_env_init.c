#include "exec.h"

void	free_listed_env(t_data *data)
{
	t_env	*tmp;

	while (data->listed_env)
	{
		tmp = data->listed_env->next;
		if (data->listed_env->key != NULL || data->listed_env->value != NULL)
		{
			free(data->listed_env->key);
			// free(data->listed_env->value);
		}
		free(data->listed_env);
		data->listed_env = tmp;
	}
}

void	add_back(t_env *new_node, t_env **listed_env)
{
	t_env	*tmp_node;

	tmp_node = (*listed_env);
	if (!new_node)
		return ;
	if ((*listed_env) == NULL)
		(*listed_env) = new_node;
	else
	{
		while (tmp_node->next != NULL && tmp_node->next != *listed_env)
			tmp_node = tmp_node->next;
		tmp_node->next = new_node;
		new_node->next = NULL;
	}
}

t_env	*create_node(t_data *data, int i)
{
	t_env	*next_node;

	next_node = malloc(sizeof(t_env));
	if (!next_node)
		return (next_node);
	next_node->key = get_key(data->env[i]);
	next_node->value = getenv(next_node->key);
	next_node->full_line = data->env[i];
	next_node->next = NULL;
	return (next_node);
}
void	init_listed_env(t_data *data)
{
	t_env	*listed_env;
	t_env	*next_node;
	int		i;

	i = 1;
	next_node = NULL;
	listed_env = NULL;
	data->listed_env = create_node(data, 0);
	if (data->env == NULL)
		print_err("ERROR : fill_listed_env 01");
	while (data->env[i])
	{
		next_node = create_node(data, i++);
		if (next_node == NULL)
		{
			free_listed_env(data);
			print_err("ERROR : fill_listed_env 02\n");
			return ;
		}
		else
			add_back(next_node, &data->listed_env);
	}
}
