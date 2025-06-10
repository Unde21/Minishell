#include "minishell.h"
#include "parsing.h"
#include <stdlib.h>

bool	remove_quote(t_data *data, char **params)
{
	size_t	i;
	char	*dup;
	int		is_quote;
	char	*str;
	bool	in_quote;
	char	tab[2];

	is_quote = NO_QUOTE;
	in_quote = false;
	dup = ft_strdup("");
	if (dup == NULL)
	{
		data->return_value = 1;
		return (false);
	}
	i = 0;
	str = *params;
	while (str[i])
	{
		if (in_quote == false && (str[i] == ASCII_DBLE_QUOTE || str[i] == ASCII_SNGL_QUOTE))
		{
			is_quote = str[i];
			in_quote = true;
		}
		else if (in_quote == true && str[i] == is_quote)
		{
			in_quote = false;
			is_quote = NO_QUOTE;
		}
		else
		{
			tab[0] = str[i];
			tab[1] = '\0';
			dup = ft_strjoin_and_free(dup, tab);
		}
		++i;
	}
	*params = dup;
	return (true);
}
