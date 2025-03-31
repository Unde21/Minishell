/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samaouch <samaouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:31:34 by samaouch          #+#    #+#             */
/*   Updated: 2025/01/09 04:27:46 by samaouch         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdint.h>

char	*ft_strrchr(const char *s, int c)
{
	int		len_s;
	char	*str;

	str = (char *)s;
	len_s = ft_strlen(s);
	if ((uint8_t)c == 0)
		return (&str[len_s]);
	while (len_s >= 0)
	{
		if (str[len_s] == (uint8_t)c)
			return (str + len_s);
		--len_s;
	}
	return (NULL);
}
