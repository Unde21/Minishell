/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samaouch <samaouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 10:17:18 by samaouch          #+#    #+#             */
/*   Updated: 2025/04/03 12:43:53 by samaouch         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

static size_t	get_word_size(char *input)
{
	size_t	word_size;

	word_size = 0;
	while (ft_isspace(*input) == false && *input != '\0')
	{
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
