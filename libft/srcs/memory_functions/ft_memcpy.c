/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samaouch <samaouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 17:58:18 by samaouch          #+#    #+#             */
/*   Updated: 2024/11/14 05:24:14 by samaouch         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdint.h>

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	uint8_t	*dst;
	uint8_t	*str;
	size_t	i;

	i = 0;
	if (!dest && !src)
		return (NULL);
	str = (uint8_t *)src;
	dst = (uint8_t *)dest;
	while (i < n)
	{
		dst[i] = str[i];
		++i;
	}
	return (dest);
}
