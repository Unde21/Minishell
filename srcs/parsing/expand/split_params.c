#include "minishell.h"
#include "parsing.h"
#include <stdlib.h>

static bool	split_and_cpy_params(char **final_array, char **params,
		size_t *index, size_t *i)
{
	char	**split;
	size_t	j;

	j = 0;
	split = ft_split(params[*i], ' ');
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

static bool	split_params_loop(char **final_array, char **params, size_t i,
		size_t *index)
{
	if (need_split_params(&params[i]) == true)
	{
		if (split_and_cpy_params(final_array, params, index, &i) == false)
			return (false);
	}
	else
	{
		final_array[*index] = ft_strdup(params[i]);
		if (final_array[*index] == NULL)
		{
			free_delim(final_array, *index);
			return (false);
		}
	}
	return (true);
}

static char	**split_params(char **params)
{
	size_t	i;
	size_t	total_len;
	size_t	index;
	char	**final_array;

	i = 0;
	total_len = 0;
	index = 0;
	count_params(params, &total_len);
	final_array = malloc(sizeof(char *) * (total_len + 1));
	if (final_array == NULL)
		return (NULL);
	while (params[i])
	{
		if (split_params_loop(final_array, params, i, &index) == false)
			return (NULL);
		++i;
	}
	free_all(params);
	final_array[index] = NULL;
	return (final_array);
}

bool	split_wildcards_file(t_cmd *cmd)
{
	t_cmd	*current;

	current = cmd;
	while (current != NULL)
	{
		if (need_split_params(current->params) == true)
		{
			current->params = split_params(current->params);
			if (current->params == NULL)
			{
				ft_dprintf(2, ERR_MALLOC);
				return (false);
			}
		}
		current = current->next;
	}
	return (true);
}
