/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_format.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samaouch <samaouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 11:40:38 by samaouch          #+#    #+#             */
/*   Updated: 2025/03/27 11:01:07 by samaouch         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>

int	print_str(char *str)
{
	size_t	i;
	int		count;

	count = 0;
	i = 0;
	if (!str)
	{
		write(1, "(null)", 6);
		return (6);
	}
	while (str[i])
	{
		count += print_char(str[i]);
		++i;
	}
	return (count);
}

int	print_char(int c)
{
	write(1, &c, 1);
	return (1);
}

int	print_nbr(int nb, int check_form, int count)
{
	long	n;

	if (check_form == 0)
		n = (long)nb;
	else
		n = (unsigned int)nb;
	if (n < 0)
	{
		print_char('-');
		n = -n;
		++count;
	}
	if (n >= 10)
		count = print_nbr(n / 10, check_form, count);
	count += print_char(n % 10 + '0');
	return (count);
}

int	print_hexa(unsigned int n, const char *base, int count)
{
	if (n >= 16)
		count = print_hexa(n / 16, base, count);
	count += print_char(base[(n % 16)]);
	return (count);
}

int	print_addr(unsigned long ptr, int count, int index)
{
	if (ptr == 0)
	{
		write(1, "(nil)", 5);
		return (5);
	}
	if (index == 0)
	{
		count += write(1, "0x", 2);
		++index;
	}
	if (ptr >= 16)
		count = print_addr(ptr / 16, count, index);
	count += print_char(HEX_LOWER[(ptr % 16)]);
	return (count);
}
