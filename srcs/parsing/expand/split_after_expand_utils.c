#include "minishell.h"
#include "parsing.h"
#include <stdlib.h>

void count_params_expand(char **params, size_t *len)
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
			if (is_special_operator(params[i][j], NO_QUOTE) == true)
				++(*len);
			else if (ft_isspace(params[i][j]) == false && in_word == false)
			{
				++(*len);
				in_word = true;
			}
			else if (ft_isspace(params[i][j]) == true)
				in_word = false;
			++j;
		}
		++i;
	}
}

static size_t	count_words_expand(char *s)
{
	bool	in_word;
	size_t	i;
	size_t	count;

	in_word = false;
	count = 0;
	i = 0;
	if (s == NULL)
		return (0);
	while (s[i])
	{
		if (is_special_operator(s[i], NO_QUOTE) == true)
			++count;
		else if (ft_isspace(s[i]) == false && in_word == false)
		{
			in_word = true;
			++count;
		}
		else if (ft_isspace(s[i]) == true && in_word == true)
			in_word = false;
		++i;
	}
	return (count);
}

static void	*free_all_delim(char **s, size_t len)
{
	size_t	i;

	i = 0;
	while (s[i] && i < len)
	{
		free(s[i]);
		s[i] = NULL;
		++i;
	}
	free(s);
	s = NULL;
	return (NULL);
}

char	**ft_split_with_charset(char *s)
{
	char	**split;
	size_t	i;
	size_t	start;
	size_t	end;
	size_t	nb_words;

	nb_words = count_words_expand(s);
	split = ft_calloc(sizeof(char *), (nb_words + 1));
	if (!split)
		return (NULL);
	i = 0;
	start = 0;
	while (s[start] && i < nb_words)
	{
		while (s[start] && ft_isspace(s[start]) == true)
			++start;
		end = start;
		while (s[end] && ft_isspace(s[end]) == false)
			++end;
		split[i++] = ft_substr(s, start, (end - start));
		if (!split[i - 1])
			return (free_all_delim(split, i - 1));
		start = end;
	}
	return (split);
}
