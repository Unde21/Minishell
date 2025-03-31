/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samaouch <samaouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 13:33:39 by samaouch          #+#    #+#             */
/*   Updated: 2025/01/09 04:27:21 by samaouch         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>

static void		*free_all(char **s, size_t len);
static size_t	count_words(char const *s, char c);

char	**ft_split(char const *s, char c)
{
	char	**split;
	size_t	i;
	size_t	start;
	size_t	end;
	size_t	nb_words;

	nb_words = count_words(s, c);
	split = ft_calloc(sizeof(char *), (nb_words + 1));
	if (!split)
		return (NULL);
	i = 0;
	start = 0;
	while (s[start] && i < count_words(s, c))
	{
		while (s[start] && s[start] == c)
			++start;
		end = start;
		while (s[end] && s[end] != c)
			++end;
		split[i++] = ft_substr(s, start, (end - start));
		if (!split[i - 1])
			return (free_all(split, i - 1));
		start = end + 1;
	}
	return (split);
}

static size_t	count_words(char const *s, char c)
{
	bool	in_word;
	size_t	i;
	size_t	count;

	in_word = false;
	count = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c && in_word == false)
		{
			in_word = true;
			++count;
		}
		else if (s[i] == c && in_word == true)
			in_word = false;
		++i;
	}
	return (count);
}

static void	*free_all(char **s, size_t len)
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
