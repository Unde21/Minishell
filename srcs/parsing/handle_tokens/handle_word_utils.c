/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_word_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samaouch <samaouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 01:33:54 by samaouch          #+#    #+#             */
/*   Updated: 2025/06/20 01:33:55 by samaouch         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

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

void	new_node_word(t_token **new, char *word, int is_quote, t_data *data)
{
	if (is_quote == ASCII_DBLE_QUOTE)
		*new = new_token(word, DBLE_QUOTE);
	else if (is_quote == ASCII_SNGL_QUOTE)
		*new = new_token(word, SNGL_QUOTE);
	else
		*new = new_token(word, WORD);
	if (*new == NULL)
		data->return_value = 1;
	data->last_type = WORD;
}
