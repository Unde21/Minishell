/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samaouch <samaouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 10:00:00 by samaouch          #+#    #+#             */
/*   Updated: 2025/03/27 10:56:28 by samaouch         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdarg.h>
#include <stddef.h>
#include <unistd.h>

int	ft_printf(const char *format, ...)
{
	va_list	params;
	int		count;

	count = 0;
	va_start(params, format);
	if (!format)
		return (-1);
	if (format_is_valid(format) == -1)
		return (-1);
	while (*format != '\0')
	{
		if (*format == '%')
		{
			if (*format + 1)
			{
				++format;
				count += check_format(&params, *format);
			}
		}
		else
			count += print_char(*format);
		++format;
	}
	va_end(params);
	return (count);
}

int	format_is_valid(const char *format)
{
	while (*format != '\0')
	{
		if (*format == '%')
		{
			++format;
			if (*format != 'c' && *format != 'd' && *format != 'i'
				&& *format != 'p' && *format != 'x' && *format != 'X'
				&& *format != 'u' && *format != 's' && *format != '%')
				return (-1);
		}
		++format;
	}
	return (0);
}

int	check_format(va_list *params, char format)
{
	int		count;

	count = 0;
	if (format == 'd' || format == 'i')
		count += print_nbr(va_arg(*params, int), 0, count);
	else if (format == 'c')
		count += print_char(va_arg(*params, int));
	else if (format == 's')
		count += print_str(va_arg(*params, char *));
	else if (format == 'p')
		count += print_addr(va_arg(*params, unsigned long), 0, 0);
	else if (format == 'u')
		count += print_nbr(va_arg(*params, unsigned int), 1, count);
	else if (format == 'x')
		count += print_hexa(va_arg(*params, unsigned int), HEX_LOWER, count);
	else if (format == 'X')
		count += print_hexa(va_arg(*params, unsigned int), HEX_UPPER, count);
	else if (format == '%')
		count += print_char('%');
	return (count);
}
