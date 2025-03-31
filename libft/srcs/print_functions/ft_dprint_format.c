/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprint_format.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samaouch <samaouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 10:59:22 by samaouch          #+#    #+#             */
/*   Updated: 2025/03/27 11:17:16 by samaouch         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	dprint_char(int c, int fd)
{
	return (write(fd, c, 1));
}

int	dprint_str(char *str, int fd)
{
	size_t	i;
	int		nb_char;

	nb_char = 0;
	i = 0;
	if (str == NULL)
	{
		write(fd, "(null)", 6);
		return (6);
	}
	while (str[i])
	{
		nb_char += dprint_char(str[i], fd);
		++i;
	}
	return (nb_char);
}

int	dprint_nbr(int nb, int check_form, int nb_char, int fd)
{
	long	n;

	if (check_form == 0)
		n = (long)nb;
	else
		n = (unsigned int)nb;
	if (n < 0)
	{
		dprint_char('-', fd);
		n = -n;
		++nb_char;
	}
	if (n >= 10)
		nb_char = dprint_nbr(n / 10, check_form, nb_char, fd);
	nb_char += dprint_char(n % 10 + '0', fd);
	return (nb_char);
}

int	dprint_hexa(unsigned int n, const char *base, int nb_char, int fd)
{
	if (n >= 16)
		nb_char = dprint_hexa(n / 16, base, nb_char, fd);
	nb_char += dprint_char(base[(n % 16)], fd);
	return (nb_char);
}

int	dprint_addr(unsigned long ptr, int nb_char, int index, int fd)
{
	if (ptr == 0)
	{
		write(fd, "(nill)", 5);
		return (5);
	}
	if (index == 0)
	{
		nb_char += write(fd, "0x", 2);
		++index;
	}
	if (ptr >= 16)
		nb_char = dprint_addr(ptr / 16, nb_char, index, fd);
	nb_char += dprint_char(HEX_LOWER[(ptr % 16)], fd);
	return (nb_char);
}
