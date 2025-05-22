/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samaouch <samaouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 11:17:56 by samaouch          #+#    #+#             */
/*   Updated: 2025/05/19 11:46:27 by samaouch         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"
#include <limits.h>
#include <stddef.h>

static int			is_overflow(unsigned long long n, const char *s, size_t i,
						int sign);
static long long	loop_atoll(const char *s, size_t i, int *check_error,
						int sign);

long long	ft_atoll(const char *nptr, int *check_error)
{
	unsigned long long	n;
	int					sign;
	size_t				i;

	i = 0;
	n = 0;
	sign = 1;
	while (nptr[i] == 32 || (nptr[i] >= 9 && nptr[i] <= 13))
		++i;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign = -sign;
		++i;
	}
	n = loop_atoll(nptr, i, check_error, sign);
	return (n * sign);
}

static long long	loop_atoll(const char *s, size_t i, int *check_error,
		int sign)
{
	unsigned long long	n;
	int					check_overflow;

	n = 0;
	while (s[i] >= '0' && s[i] <= '9')
	{
		check_overflow = is_overflow(n, s, i, sign);
		if (check_overflow == -1)
		{
			++*(check_error);
			return (-1);
		}
		else if (check_overflow == 0)
		{
			++*(check_error);
			return (0);
		}
		n = n * 10 + (s[i] - '0');
		++i;
	}
	return (n);
}

static int	is_overflow(unsigned long long n, const char *s, size_t i, int sign)
{
	if (sign < 0)
	{
		if (n > ((unsigned long long)(-(LLONG_MIN + (s[i] - '0')) / 10)))
			return (0);
	}
	else if (sign > 0)
	{
		if (n > ((unsigned long long)(LLONG_MAX - (s[i] - '0')) / 10))
			return (0);
	}
	return (1);
}
