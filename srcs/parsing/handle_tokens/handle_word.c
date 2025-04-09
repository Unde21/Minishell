/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samaouch <samaouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 10:17:18 by samaouch          #+#    #+#             */
/*   Updated: 2025/04/09 18:35:07 by samaouch         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

static size_t	get_word_size(char *input, bool *is_quote)
{
	size_t	word_size;
	int		check_quote;

	word_size = 0;
	check_quote = wich_quote(*input);
	if (check_quote != 0)
	{
		++input;
		*is_quote = true;
	}
	while ((ft_isspace(*input) == false && *input != '\0')
		|| (*is_quote == true && *input != '\0'))
	{
		if (wich_quote(*input) == ASCII_DBLE_QUOTE
			&& check_quote == ASCII_DBLE_QUOTE)
			break ;
		else if (wich_quote(*input) == ASCII_SNGL_QUOTE
			&& check_quote == ASCII_SNGL_QUOTE)
			break ;
		++word_size;
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
		ft_dprintf(2, ERR_MALLOC);
		return (NULL);
	}
	if (wich_quote(*input) != 0)
		++input;
	while (*input != '\0' && i < word_size)
	{
		word[i] = *(input + i);
		++i;
	}
	word[i] = '\0';
	return (word);
}

size_t	handle_word(char *input, t_token **new)
{
	size_t	word_size;
	char	*word;
	bool	is_quote;

	is_quote = false;
	word_size = get_word_size(input, &is_quote);
	if (word_size == 0)
		return (1);
	word = extract_word(input, word_size);
	if (word == NULL)
		return (word_size);
	*new = new_token(word, WORD);
	if (is_quote == true && word_size != 0)
		word_size += 2;
	return (word_size);
}
