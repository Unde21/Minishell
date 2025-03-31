/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samaouch <samaouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 23:26:41 by samaouch          #+#    #+#             */
/*   Updated: 2025/01/21 23:29:53 by samaouch         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <unistd.h>

char	*get_next_line(int fd)
{
	static char	buffer[MAX_FD][BUFFER_SIZE + 1];
	char		*line;
	int			bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= MAX_FD)
		return (NULL);
	line = malloc(sizeof(char));
	if (line == NULL)
		return (NULL);
	line[0] = '\0';
	bytes_read = 1;
	while (bytes_read > 0)
	{
		line = ft_strnjoin(line, buffer[fd], '\n');
		if (line == NULL)
			return (NULL);
		if (ft_strchr(line, '\n'))
			break ;
		bytes_read = read_file(fd, buffer[fd]);
		if ((bytes_read == 0 && line[0] == '\0') || bytes_read < 0)
			return (ft_free(line));
	}
	clear_buffer(buffer[fd]);
	return (line);
}

int	read_file(int fd, char *buffer)
{
	int	bytes_read;

	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (bytes_read < 0)
	{
		buffer[0] = '\0';
		return (-1);
	}
	if (bytes_read == 0 && buffer[0] == '\0')
		return (0);
	buffer[bytes_read] = '\0';
	return (bytes_read);
}

char	*clear_buffer(char *buffer)
{
	char	*newline_pos;

	newline_pos = ft_strchr(buffer, '\n');
	if (buffer[0] && newline_pos)
	{
		newline_pos++;
		ft_strlcpy(buffer, newline_pos, ft_strlen_delim(buffer, 0));
	}
	return (buffer);
}
