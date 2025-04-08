/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samaouch <samaouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 10:17:18 by samaouch          #+#    #+#             */
/*   Updated: 2025/04/08 15:13:42 by samaouch         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

static size_t	get_word_size(char *input)
{
	size_t	word_size;
	int		check_quote;

	word_size = 0;
	check_quote = wich_quote(*input);
	if (check_quote != 0)
	{
		++input;
		++word_size;
	}
	while ((ft_isspace(*input) == false && *input != '\0')
		|| (check_quote != 0 && *input != '\0'))
	{
		++word_size;
		if (wich_quote(*input) == ASCII_DBLE_QUOTE
			&& check_quote == ASCII_DBLE_QUOTE)
			break ;
		else if (wich_quote(*input) == ASCII_SNGL_QUOTE
			&& check_quote == ASCII_SNGL_QUOTE)
			break ;
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

	word_size = get_word_size(input);
	word = extract_word(input, word_size);
	if (word == NULL)
		return (word_size);
	*new = new_token(word, WORD);
	return (word_size);
}
