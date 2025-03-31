/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samaouch <samaouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 17:45:44 by samaouch          #+#    #+#             */
/*   Updated: 2025/01/09 04:27:30 by samaouch         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t		i;
	size_t		len_src;
	size_t		len_dst;

	i = 0;
	if (!dst && size == 0)
		return (0);
	len_dst = ft_strlen(dst);
	len_src = ft_strlen(src);
	if (len_dst >= size)
		return (len_src + size);
	while (src[i] && i + len_dst + 1 < size)
	{
		dst[len_dst + i] = src[i];
		++i;
	}
	dst[len_dst + i] = '\0';
	return (len_dst + len_src);
}
