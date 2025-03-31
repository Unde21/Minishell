/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samaouch <samaouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 13:55:04 by samaouch          #+#    #+#             */
/*   Updated: 2025/01/09 04:26:31 by samaouch         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdint.h>

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	uint8_t	*dst;
	uint8_t	*str;

	if (!dest && !src)
		return (NULL);
	dst = (uint8_t *)dest;
	str = (uint8_t *)src;
	if (dst < str)
		ft_memcpy(dest, src, n);
	else
	{
		while (n--)
			dst[n] = str[n];
	}
	return (dest);
}
