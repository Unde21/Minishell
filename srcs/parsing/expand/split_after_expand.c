#include "minishell.h"
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

static char **split_expand(char **params)
{
	size_t	i;
	size_t	total_len;
	size_t	index;
	char	**final_array;

	i = 0;
	total_len = 0;
	index = 0;
	count_params_expand(params, &total_len);
	final_array = malloc(sizeof(char *) * (total_len + 1));
	if (final_array == NULL)
		return (NULL);
	while (params[i])
	{
		if (split_and_cpy_expand(final_array, params, &index, &i) == false)
			return (NULL);
		++i;
	}
	free_all(params);
	final_array[index] = NULL;
	return (final_array);
}

static bool need_split_expand(t_cmd *cmd, char **params)
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

bool	handle_split_expand(t_cmd *cmd)
{
	t_cmd *current;

	current = cmd;
	while (current != NULL)
	{
		if (need_split_expand(cmd, current->params) == true)
		{
			current->params = split_expand(current->params);
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
