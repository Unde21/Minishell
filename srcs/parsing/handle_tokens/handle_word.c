

#include "minishell.h"
#include <stdlib.h>

static bool	is_special_operator(char input, int is_quote)
{
	if ((input == '|' && is_quote == NO_QUOTE) || (input == '>'
			&& is_quote == NO_QUOTE) || (input == '<'
			&& is_quote == NO_QUOTE))
		return (true);
	return (false);
}

static int	save_quote(char input)
{
	int	is_quote;

	is_quote = NO_QUOTE;
	if (input == ASCII_DBLE_QUOTE)
		is_quote = ASCII_DBLE_QUOTE;
	else if (input == ASCII_SNGL_QUOTE)
		is_quote = ASCII_SNGL_QUOTE;
	return (is_quote);
}

static size_t	get_word_size(char *input, int is_quote)
{
	size_t	word_size;
	int		count_quote;

	count_quote = 0;
	word_size = 0;
	skip_quote_dollar(&input, is_quote, &word_size, &count_quote);
	while ((ft_isspace(*input) == false && *input != '\0'
			&& save_quote(*input) == NO_QUOTE && is_quote == NO_QUOTE)
		|| (is_quote != NO_QUOTE && *input != '\0' && count_quote < 2))
	{
		if (is_special_operator(*input, is_quote) == true)
			break ;
		++word_size;
		if (*input == is_quote)
			++count_quote;
		++input;
	}
	return (word_size);
}

static char	*extract_word(char *input, size_t word_size)
{
	size_t	i;
	char	*word;

	i = 0;
	word = malloc(sizeof(char) * (word_size + 1));
	if (word == NULL)
	{
		print_err(ERR_MALLOC);
		return (NULL);
	}
	while (*input != '\0' && i < word_size)
	{
		word[i] = *(input + i);
		++i;
	}
	word[i] = '\0';
	return (word);
}

static bool	is_quote_missing(char *word, size_t word_size, int check_quote)
{
	// invalid read of size 1 si input = \t 
	if (word_size == 1 && check_quote != NO_QUOTE)
	{
		print_err(MISS_DBLE_QUOTE);
		return (true);
	}
	else if (word_size == 1 && check_quote != NO_QUOTE)
	{
		print_err(MISS_SNGL_QUOTE);
		return (true);
	}
	if ((word[word_size - 1] != ASCII_DBLE_QUOTE
			&& check_quote == ASCII_DBLE_QUOTE) || (check_quote == NO_QUOTE
			&& word[word_size - 1] == ASCII_DBLE_QUOTE))
	{
		print_err(MISS_DBLE_QUOTE);
		return (true);
	}
	else if ((word[word_size - 1] != ASCII_SNGL_QUOTE
			&& check_quote == ASCII_SNGL_QUOTE) || (check_quote == NO_QUOTE
			&& word[word_size - 1] == ASCII_SNGL_QUOTE))
	{
		print_err(MISS_SNGL_QUOTE);
		return (true);
	}
	return (false);
}

size_t	handle_word(char *input, t_token **new, bool *error)
{
	size_t	word_size;
	char	*word;
	int		is_quote;

	is_quote = 0;
	is_quote = save_quote(*input);
	word_size = get_word_size(input, is_quote);
	word = extract_word(input, word_size);
	if (is_quote_missing(word, word_size, is_quote) == true)
	{
		*error = true;
		free(word);
		return (ft_strlen(input));
	}
	if (is_quote == ASCII_DBLE_QUOTE)
		*new = new_token(word, DBLE_QUOTE);
	else if (is_quote == ASCII_SNGL_QUOTE)
		*new = new_token(word, SNGL_QUOTE);
	else
		*new = new_token(word, WORD);
	free(word);
	return (word_size);
}
