/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samaouch <samaouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 19:55:31 by samaouch          #+#    #+#             */
/*   Updated: 2025/01/09 04:27:52 by samaouch         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*dst;
	size_t	len_s;
	size_t	cst_start;

	cst_start = (size_t)start;
	len_s = ft_strlen(s);
	if (cst_start >= len_s)
		len = 0;
	else if (len >= len_s - cst_start)
		len = len_s - cst_start;
	dst = malloc(sizeof(char) * (len + 1));
	if (!dst)
		return (NULL);
	if (len != 0)
	{
		ft_strlcpy(dst, s + cst_start, len + 1);
		return (dst);
	}
	dst[len] = '\0';
	return (dst);
}
