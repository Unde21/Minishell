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

char	*ft_strndup(char *s, size_t *j)
{
	size_t	i;
	size_t	len;
	char	*dup;
	bool	in_quote;

	in_quote = false;
	len = new_length(s);
	dup = malloc(sizeof(char) * (len + 1));
	if (dup == NULL)
		return (NULL);
	i = 0;
	len = 0;
	while (s[i])
	{
		if (s[i] != ASCII_DBLE_QUOTE)
		{
			dup[len] = s[i];
			++len;
		}
		++i;
	}
	dup[len] = '\0';
	*j += i;
	return (dup);
}

bool	remove_quote_loop(char **params, char **dup)
{
	size_t	i;
	size_t	j;

	i = 0;
	while(params[i])
	{
		j = 0;
		while (params[i][j])
		{

			if (params[i][j++] == ASCII_DBLE_QUOTE)
			{
				ft_strjoin_and_free(dup[i], ft_strndup(&params[i][j], &j));
				if (dup[i] == NULL)
				{
					free_delim(dup, i);
					return (false);
				}
				free(params[i]);
				params[i] = dup[i];
			}
			else
			{
				size_t k = j;
				while (params[i][k])
					++k;
				dup[i] = malloc(sizeof(char) * (k +1));
				// secure
				k =0;
				while (params[i][j])
				{
					dup[i][k] = params[i][j];
					++j;
					++k;
				}
			}
			++j;
		}
		++i;
	}
	return (true);
}

bool	remove_quote(t_data *data, char **params)
{
	size_t	len;
	char 	**tmp;
	char	**dup;

	tmp = params;
	len = ft_strlen(*params);
	dup = malloc(sizeof(char *) * (len + 1));
	if (dup == NULL)
	{
		data->return_value = 1;
		return (print_err(ERR_MALLOC));
	}
	if(remove_quote_loop(params, dup) == false)
	{
		data->return_value = 1;
		ft_dprintf(2, ERR_MALLOC);
		return (false);
	}
	return (true);
}
