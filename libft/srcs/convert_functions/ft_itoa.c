/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samaouch <samaouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 17:29:01 by samaouch          #+#    #+#             */
/*   Updated: 2024/11/14 05:20:36 by samaouch         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static size_t	check_nb_size(int n);

char	*ft_itoa(int n)
{
	long	nb;
	size_t	len;
	char	*s;

	nb = (long)n;
	len = check_nb_size(nb);
	s = malloc(sizeof(char) * len + 1);
	if (!s)
		return (NULL);
	s[len] = '\0';
	if (nb < 0)
		nb = -nb;
	while (len-- > 0)
	{
		s[len] = (nb % 10) + 48;
		nb /= 10;
	}
	if (n < 0)
		s[0] = '-';
	return (s);
}

static size_t	check_nb_size(int n)
{
	size_t	i;

	i = 0;
	if (n < 0)
	{
		n = -n;
		++i;
	}
	while (n != 0)
	{
		++i;
		n /= 10;
	}
	if (i == 0)
		++i;
	return (i);
}
