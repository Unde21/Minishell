/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samaouch <samaouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 10:50:19 by samaouch          #+#    #+#             */
/*   Updated: 2025/03/27 11:23:47 by samaouch         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	handle_format(va_list *params, char format, int fd)
{
	int	nb_char;

	nb_char = 0;
	if (format == 'd' || format == 'i')
		nb_char += dprint_nbr(va_arg(*params, int), 0, nb_char, fd);
	else if (format == 'c')
		nb_char += dprint_char(va_arg(*params, int), fd);
	else if (format == 's')
		nb_char += dprint_str(va_arg(*params, char *), fd);
	else if (format == 'p')
		nb_char += dprint_addr(va_arg(*params, unsigned long), 0, 0, fd);
	else if (format == 'u')
		nb_char += dprint_nbr(va_arg(*params, unsigned int), 1, nb_char, fd);
	else if (format == 'x')
		nb_char += dprint_hexa(va_arg(*params, unsigned int), HEX_LOWER,
				nb_char, fd);
	else if (format == 'X')
		nb_char += dprint_hexa(va_arg(*params, unsigned int), HEX_UPPER,
				nb_char, fd);
	else if (format == '%')
		nb_char += dprint_char('%', fd);
	return (nb_char);
}

int	ft_dprintf(int fd, const char *format, ...)
{
	va_list	params;
	int		nb_char;

	nb_char = 0;
	va_start(params, format);
	if (!format)
		return (-1);
	if (format_is_valid(format) == -1)
		return (-1);
	while (*format)
	{
		if (*format == '%')
		{
			if (*format + 1)
			{
				++format;
				nb_char += handle_format(&params, *format, fd);
			}
		}
		else
			nb_char += dprint_char(*format, fd);
		++format;
	}
	va_end(params);
	return (nb_char);
}
