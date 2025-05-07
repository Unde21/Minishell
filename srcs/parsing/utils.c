#include "minishell.h"
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

bool	print_err(char *str_error)
{
	ft_dprintf(2, "%s", str_error);
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

char	*ft_strjoin_and_free(char *s1, char *s2)
{
	char	*join;
	size_t	i;
	size_t	len;
	size_t	j;

	i = 0;
	len = ft_strlen(s1) + ft_strlen(s2);
	join = malloc(sizeof(char) * (len + 1));
	if (!join)
		return (NULL);
	while (s1[i])
	{
		join[i] = s1[i];
		++i;
	}
	j = 0;
	while (s2[j])
	{
		join[i + j] = s2[j];
		++j;
	}
	join[i + j] = '\0';
	free(s1);
	return (join);
}
