/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samaouch <samaouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 19:08:42 by samaouch          #+#    #+#             */
/*   Updated: 2024/11/14 05:23:57 by samaouch         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdint.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	uint8_t	*str1;
	uint8_t	*str2;
	size_t	i;

	i = 0;
	str1 = (uint8_t *)s1;
	str2 = (uint8_t *)s2;
	if (n == 0)
		return (0);
	while (str1[i] == str2[i] && i < n - 1)
		++i;
	return (str1[i] - str2[i]);
}
