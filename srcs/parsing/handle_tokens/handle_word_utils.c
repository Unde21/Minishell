#include "parsing.h"

bool	is_special_operator(char input, int is_quote)
{
	if ((input == '|' && is_quote == NO_QUOTE) || (input == '>'
			&& is_quote == NO_QUOTE) || (input == '<' && is_quote == NO_QUOTE))
		return (true);
	return (false);
}

int	save_quote(char input)
{
	int	is_quote;

	is_quote = NO_QUOTE;
	if (input == ASCII_DBLE_QUOTE)
		is_quote = ASCII_DBLE_QUOTE;
	else if (input == ASCII_SNGL_QUOTE)
		is_quote = ASCII_SNGL_QUOTE;
	return (is_quote);
}

void	new_node_word(t_token **new, char *word, int is_quote, bool *error)
{
	if (is_quote == ASCII_DBLE_QUOTE)
		*new = new_token(word, DBLE_QUOTE);
	else if (is_quote == ASCII_SNGL_QUOTE)
		*new = new_token(word, SNGL_QUOTE);
	else
		*new = new_token(word, WORD);
	if (*new == NULL)
		*error = true;
}
