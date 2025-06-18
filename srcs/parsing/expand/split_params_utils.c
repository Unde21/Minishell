#include "parsing.h"
#include <stdlib.h>

bool	need_split_params(t_cmd *cmd, char **params)
{
	size_t	i;

	i = 0;
	while (params[i])
	{
		if (ft_strchr(params[i], '*') != NULL
			&& ft_strchr(params[i], '/') != NULL)
		{
			++i;
			continue ;
		}
		else if (cmd->args[i].is_wildcards == true
			&& ft_strchr(params[i], '/') != NULL)
			return (true);
		++i;
	}
	return (false);
}

void	count_params(char **params, size_t *len)
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
			if (params[i][j] != '/' && in_word == false)
			{
				(*len)++;
				in_word = true;
			}
			else if (params[i][j] == '/')
				in_word = false;
			j++;
		}
		i++;
	}
}

void	free_delim(char **s, size_t	delim)
{
	while (delim > 0)
	{
		ft_printf("%s\n", s[delim]);
		free(s[delim]);
		--delim;
	}
	free(s);
}
