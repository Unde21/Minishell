/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samaouch <samaouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 16:14:44 by samaouch          #+#    #+#             */
/*   Updated: 2024/11/14 05:25:21 by samaouch         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdint.h>

void	*ft_memset(void *s, int c, size_t n)
{
	uint8_t	*str;
	size_t	i;

	i = 0;
	str = (uint8_t *)s;
	while (n > 0)
	{
		str[i] = c;
		--n;
		++i;
	}
	return (s);
}
