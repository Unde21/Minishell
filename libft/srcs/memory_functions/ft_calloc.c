/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samaouch <samaouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 19:11:31 by samaouch          #+#    #+#             */
/*   Updated: 2025/01/09 04:26:22 by samaouch         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <stdint.h>

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*calloc;
	size_t	total_size;

	if (!nmemb || !size)
		total_size = 0;
	else
	{
		if (nmemb > SIZE_MAX / size)
			return (NULL);
		total_size = size * nmemb;
	}
	calloc = malloc(total_size);
	if (!calloc)
		return (NULL);
	ft_bzero(calloc, total_size);
	return (calloc);
}
