#include "minishell.h"
#include "parsing.h"
#include <stdlib.h>

size_t	new_length(char *s)
{
	size_t	len;
	size_t	i;

	i = 0;
	len = 0;
	while (s[i])
	{
		if (s[i] != ASCII_DBLE_QUOTE)
			++len;
		++i;
	}
	return (len);
}

bool	duplicate_params(size_t *i, int quote, char *params, char **dup)
{
	size_t	index;
	char	*tmp;

	index = *i;
	while (params[index] != quote && params[index])
		++index;
	tmp = malloc(sizeof(char) * (index - *i + 1));
	if (tmp == NULL)
		return (false);
	index = 0;
	while (params[*i] != quote && params[*i])
	{
		tmp[index] = params[*i];
		++(*i);
		++index;
	}
	tmp[index] = '\0';
	*dup = ft_strjoin_and_free(*dup, tmp);
	free(tmp);
	if (*dup == NULL)
	{
		return (false);
	}
	return (true);
}

bool	remove_quote_loop(char *params, char **dup)
{
	size_t	i;
	int		quote;

	i = 0;
	quote = wich_quote(params);
	while (params[i])
	{
		if (params[i] != quote)
		{
			if (duplicate_params(&i, quote, params, dup) == false)
				return (false);
		}
		else
			++i;
	}
	return (true);
}

bool	remove_quote(t_data *data, char **params)
{
	char	*dup;

	dup = ft_strdup("");
	if (dup == NULL)
		return (print_err(ERR_MALLOC));
	if (remove_quote_loop(*params, &dup) == false)
	{
		data->return_value = 1;
		if (dup != NULL)
			free(dup);
		return (print_err(ERR_MALLOC));
	}
	free(*params);
	*params = dup;
	return (true);
}
