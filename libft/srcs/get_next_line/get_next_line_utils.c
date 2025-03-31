/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samaouch <samaouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 23:27:22 by samaouch          #+#    #+#             */
/*   Updated: 2025/01/21 23:29:48 by samaouch         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>

char	*ft_strchr(const char *s, int c)
{
	size_t	i;
	char	*str;

	if (!s)
		return (NULL);
	str = (char *)s;
	i = 0;
	while (str[i])
	{
		if (str[i] == (uint8_t)c)
			return (&str[i]);
		++i;
	}
	return (NULL);
}

size_t	ft_strlen_delim(const char *str, int check)
{
	size_t	len;

	len = 0;
	if (!str)
		return (0);
	if (check == 1)
	{
		while (str[len])
		{
			if (str[len] == '\n')
				return (len + 1);
			++len;
		}
	}
	else
	{
		while (str[len])
			++len;
	}
	return (len);
}

char	*ft_strnjoin(char const *s1, char const *s2, int c)
{
	char	*join;
	ssize_t	i;
	ssize_t	len;
	ssize_t	j;

	i = -1;
	if (!s1 || !s2)
		return (ft_free((char *)s1));
	len = ft_strlen_delim(s1, 0) + ft_strlen_delim(s2, 1);
	join = malloc(sizeof(char) * len + 1);
	if (join == NULL)
		return (ft_free((char *)s1));
	while (s1 && s1[++i])
		join[i] = s1[i];
	j = 0;
	while (s2[j] && s2[j] != c)
	{
		join[i + j] = s2[j];
		++j;
	}
	if (s2[j] == c)
		join[i + j++] = '\n';
	ft_free((char *)s1);
	join[i + j] = '\0';
	return (join);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (!src || !dst)
		return (0);
	if (size <= 0)
		return (ft_strlen_delim(src, 0));
	while (src[i] && i < size - 1)
	{
		dst[i] = src[i];
		++i;
	}
	dst[i] = '\0';
	return (ft_strlen_delim(src, 0));
}

void	*ft_free(char *s)
{
	if (s)
	{
		free(s);
		s = NULL;
	}
	return (NULL);
}
