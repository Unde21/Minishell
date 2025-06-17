#include "exec.h"
#include "parsing.h"
#include <stdlib.h>

void	free_listed_env(t_data *data)
{
	t_env	*tmp;

	while (data->listed_env)
	{
		tmp = data->listed_env->next;
		if (data->listed_env->key != NULL)
			free(data->listed_env->key);
		if (data->listed_env->value != NULL)
			free(data->listed_env->value);
		free(data->listed_env);
		data->listed_env = tmp;
	}
	data->listed_env = NULL;
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
		while (tmp_node->next != NULL)
			tmp_node = tmp_node->next;
		tmp_node->next = new_node;
		new_node->next = NULL;
	}
}

static bool	fill_next_node(t_env *next_node, t_data *data, int i)
{
	next_node->key = get_key(data->env[i]);
	if (next_node->key == NULL)
	{
		free(next_node);
		return (false);
	}
	next_node->value = get_value(data->env[i]);
	if (next_node->value == NULL)
	{
		free(next_node->key);
		free(next_node);
		return (false);
	}
	next_node->full_line = ft_strdup(data->env[i]);
	if (next_node->full_line == NULL)
	{
		free(next_node->key);
		free(next_node->value);
		free(next_node);
		return (false);
	}
	next_node->printed = 0;
	next_node->next = NULL;
	return (true);
}

t_env	*create_node(t_data *data, int i)
{
	t_env	*next_node;

	next_node = malloc(sizeof(t_env));
	if (!next_node)
		return (next_node);
	if (data->env[0] == NULL)
	{
		next_node->key = NULL;
		next_node->value = NULL;
		next_node->full_line = NULL;
		next_node->printed = 0;
		next_node->next = NULL;
	}
	else if (fill_next_node(next_node, data, i) == false)
		return (NULL);
	return (next_node);
}

void	init_listed_env(t_data *data)
{
	t_env	*next_node;
	int		i;

	i = 1;
	next_node = NULL;
	data->listed_env = create_node(data, 0);
	if (data->listed_env == NULL)
	{
		data->return_value = 1;
		print_err_null(ERR_MALLOC);
		return ;
	}
	while (data->env[i])
	{
		next_node = create_node(data, i++);
		if (next_node == NULL)
		{
			data->return_value = 1;
			free_listed_env(data);
			print_err_null(ERR_MALLOC);
			return ;
		}
		else
			add_back(next_node, &data->listed_env);
	}
}
