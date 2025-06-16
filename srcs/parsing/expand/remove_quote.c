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

bool	remove_quote_loop(char *params, char **dup)
{
	size_t	i;
	char	*tmp;
	int		quote;

	tmp = NULL;
	i = 0;
	quote = wich_quote(params);
	while(params[i])
	{
		if (params[i] != quote)
		{
			size_t k = i;
			while (params[k] != quote && params[k])
			{	
				++k;
			}
			tmp = malloc(sizeof(char) * (k + 1));
			// secure
			k = 0;
			while (params[i] != quote && params[i])
			{
				tmp[k] = params[i];
				++i;
				++k;
			}
			tmp[k] = '\0';
			*dup = ft_strjoin_and_free(*dup, tmp);
			//secure
			free(tmp);
		}
		else
			++i;
	}
	return (true);
}

bool	remove_quote(t_data *data, char **params)
{
	size_t	len;
	char 	*tmp;
	char	*dup;

	tmp = *params;
	dup = ft_strdup("");
	//secure
	len = ft_strlen(*params);
	if(remove_quote_loop(*params, &dup) == false)
	{
		data->return_value = 1;
		ft_dprintf(2, ERR_MALLOC);
		return (false);
	}
	*params = dup;
	return (true);
}
