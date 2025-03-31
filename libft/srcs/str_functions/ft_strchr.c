/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samaouch <samaouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 15:51:49 by samaouch          #+#    #+#             */
/*   Updated: 2025/01/09 04:27:17 by samaouch         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdint.h>

char	*ft_strchr(const char *s, int c)
{
	size_t	i;
	char	*str;

	str = (char *)s;
	i = 0;
	if ((uint8_t)c == '\0')
		return (&str[ft_strlen(str)]);
	while (str[i])
	{
		if (str[i] == (uint8_t)c)
			return (&str[i]);
		++i;
	}
	return (NULL);
}
