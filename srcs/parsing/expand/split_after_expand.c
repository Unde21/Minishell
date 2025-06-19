#include "parsing.h"
#include <stdlib.h>

static bool	split_and_cpy_expand(char **final_array, char **params,
		size_t *index, size_t *i)
{
	char	**split;
	size_t	j;

	j = 0;
	split = ft_split_with_charset(params[*i]);
	if (split == NULL)
	{
		free_delim(final_array, *index);
		return (false);
	}
	while (split[j])
	{
		final_array[*index] = split[j];
		++j;
		++*index;
	}
	free(split);
	return (true);
}

static char	**split_expand(t_data *data, char **params, size_t index, size_t i)
{
	char	**final_array;

	count_params_expand(params, &i);
	final_array = malloc(sizeof(char *) * (i + 1));
	if (final_array == NULL)
	{
		free_all(params);
		data->return_value = 1;
		return (NULL);
	}
	i = 0;
	while (params[i])
	{
		if (split_and_cpy_expand(final_array, params, &index, &i) == false)
		{
			data->return_value = 1;
			free_all(params);
			return (NULL);
		}
		i++;
	}
	free_all(params);
	final_array[index] = NULL;
	return (final_array);
}

static bool	need_split_expand(t_cmd *cmd, char **params)
{
	size_t	i;

	i = 0;
	while (params[i])
	{
		if (cmd->args[i].is_quote == false)
			return (true);
		++i;
	}
	return (false);
}

bool	handle_split_expand(t_data *data, t_cmd *cmd)
{
	size_t	index;
	size_t	i;
	t_cmd	*current;

	index = 0;
	i = 0;
	current = cmd;
	while (current != NULL)
	{
		if (need_split_expand(cmd, current->params) == true)
		{
			current->params = split_expand(data, current->params, index, i);
			if (current->params == NULL)
				return (print_err_false(ERR_MALLOC));
		}
		current = current->next;
	}
	return (true);
}
