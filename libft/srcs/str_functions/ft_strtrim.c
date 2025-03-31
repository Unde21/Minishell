/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samaouch <samaouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 10:37:36 by samaouch          #+#    #+#             */
/*   Updated: 2025/01/09 04:27:49 by samaouch         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int		new_length(char const *s1, char const *set);
static size_t	is_in_charset(char const *s1, char const *set, int pos);

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	size_t	i;
	size_t	len;

	i = 0;
	len = new_length(s1, set);
	while (is_in_charset(s1, set, i) != 0)
		++i;
	str = ft_substr(s1, i, len);
	return (str);
}

static size_t	is_in_charset(char const *s1, char const *set, int pos)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (s1[pos] == set[i])
			return (-1);
		++i;
	}
	return (0);
}

static int	new_length(char const *s1, char const *set)
{
	size_t	i;
	size_t	new_len;

	new_len = 0;
	i = 0;
	new_len = ft_strlen(s1);
	while (is_in_charset(s1, set, i) != 0 && new_len > 0)
	{
		++i;
		--new_len;
	}
	i = ft_strlen(s1) - 1;
	while (is_in_charset(s1, set, i) != 0 && new_len > 0)
	{
		--i;
		--new_len;
	}
	return (new_len);
}
