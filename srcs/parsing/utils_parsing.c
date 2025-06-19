#include "parsing.h"
#include <stdlib.h>

int	wich_quote(char *input)
{
	size_t	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == (char)ASCII_DBLE_QUOTE)
			return (ASCII_DBLE_QUOTE);
		else if (input[i] == (char)ASCII_SNGL_QUOTE)
			return (ASCII_SNGL_QUOTE);
		++i;
	}
	return (0);
}

bool	is_redir_type(t_token_type type)
{
	if (type == REDIR_IN || type == REDIR_OUT || type == HERE_DOC
		|| type == APPEND)
		return (true);
	return (false);
}

void	skip_quote_dollar(char **input, int is_quote, size_t *word_size,
		int *count_quote)
{
	if (**input == ASCII_DOLLAR)
	{
		++(*word_size);
		++(*input);
	}
	if (is_quote != NO_QUOTE)
	{
		++(*count_quote);
		++(*input);
		++(*word_size);
	}
}

static	char	*free_return(char *s1)
{
	if (s1 != NULL)
		free(s1);
	return (NULL);
}

char	*ft_strjoin_and_free(char *s1, char *s2)
{
	char	*join;
	int		i;
	int		len;
	int		j;

	i = -1;
	if (s1 == NULL || s2 == NULL)
		return (free_return(s1));
	len = ft_strlen(s1) + ft_strlen(s2);
	join = malloc(sizeof(char) * (len + 1));
	if (join == NULL)
	{
		free(s1);
		return (NULL);
	}
	while (s1[++i])
		join[i] = s1[i];
	j = -1;
	while (s2[++j])
		join[i + j] = s2[j];
	join[i + j] = '\0';
	free(s1);
	// free(s2);  // ??? leaks
	return (join);
}
