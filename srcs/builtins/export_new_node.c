#include "builtins.h"
#include "parsing.h"
#include <stdlib.h>
#include "exec.h"

static bool	fill_new_node(t_data *data, t_env *new_node, char *params)
{
	new_node->key = get_key(params);
	if (new_node->key == NULL)
	{
		free(new_node);
		return (false);
	}
	new_node->value = get_value(data, params);
	if (new_node->value == NULL)
	{
		free(new_node->key);
		free(new_node);
		return (print_err_false(ERR_MALLOC));
	}
	new_node->full_line = ft_strdup(params);
	if (new_node->full_line == NULL)
	{
		free(new_node->value);
		free(new_node->key);
		free(new_node);
		return (print_err_false(ERR_MALLOC));
	}
	new_node->printed = 0;
	new_node->next = NULL;
	return (true);
}

bool	export_new(t_data *data, t_env *listed_env, char *params)
{
	t_env	*new_node;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (print_err_false(ERR_MALLOC));
	else
	{
		if (fill_new_node(data, new_node, params) == false)
			return (false);
	}
	add_back(new_node, &listed_env);
	return (true);
}
