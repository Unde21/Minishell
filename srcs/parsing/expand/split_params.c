#include "minishell.h"
#include "parsing.h"
#include <stdlib.h>

static bool	need_split_params(char **params)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (params[i])
	{
		j = 0;
		while (params[i][j])
		{
			if (ft_isspace(params[i][j]) == true)
				return (true);
			++j;
		}
		++i;
	}
	return (false);
}

static void	count_params(char **params, size_t *len)
{
	size_t	i;
	size_t	j;
	bool	in_word;

	i = 0;
	while (params[i])
	{
		j = 0;
		in_word = false;
		while (params[i][j])
		{
			if (ft_isspace(params[i][j]) == false && in_word == false)
			{
				(*len)++;
				in_word = true;
			}
			else if (ft_isspace(params[i][j]) == true)
				in_word = false;
			j++;
		}
		i++;
	}
}

static char	**split_params(char **params)
{
	size_t	i;
	size_t	j;
	size_t	total_len;
	size_t	index;
	char	**final_array;
	char	**split;

	i = 0;
	total_len = 0;
	index = 0;
	count_params(params, &total_len);
	final_array = malloc(sizeof(char *) * (total_len + 1));
	if (final_array == NULL)
		return (NULL);
	while (params[i])
	{
		if (need_split_params(&params[i]) == true)
		{
			split = ft_split(params[i], ' ');
			if (split == NULL)
			{
				while (index > 0)
				{
					free(final_array[index]);
					--index;
				}
				free(final_array);
				return (NULL);
			}
			j = 0;
			while (split[j])
			{
				final_array[index] = split[j];
				++j;
				++index;
			}
			free(split);
		}
		else
		{
			final_array[index] = ft_strdup(params[i]);
			if (final_array[index] == NULL)
			{
				while (index > 0)
				{
					free(final_array[index]);
					--index;
				}
				free(final_array);
				return (NULL);
			}
		}
		++i;
	}
	free_all(params);
	final_array[index] = NULL;
	return (final_array);
	
}

bool	split_wildcards_file(t_cmd *cmd)
{
	t_cmd *current;

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
