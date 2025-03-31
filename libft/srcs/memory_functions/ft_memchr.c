/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samaouch <samaouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 18:22:38 by samaouch          #+#    #+#             */
/*   Updated: 2024/11/14 05:23:47 by samaouch         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdint.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	uint8_t	*str;
	size_t	i;

	i = 0;
	str = (uint8_t *)s;
	while (i < n)
	{
		if (str[i] == (uint8_t)c)
			return (str + i);
		++i;
	}
	return (NULL);
}
