/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samaouch <samaouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 01:30:59 by samaouch          #+#    #+#             */
/*   Updated: 2025/06/20 01:31:00 by samaouch         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "parsing.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

char	*get_random_name(char *here_doc)
{
	char	c;
	int		i;
	int		fd;

	i = 0;
	here_doc = malloc(sizeof(char) * 26);
	if (!here_doc)
		return (print_err_null(ERR_MALLOC));
	fd = open("/dev/random", O_RDONLY);
	if (fd == -1)
	{
		free(here_doc);
		return (print_err_null(ERR_OP_FD));
	}
	while (i < 25)
	{
		read(fd, &c, 1);
		if (ft_isprint(c) && c != '/')
			here_doc[i++] = c;
	}
	here_doc[i] = '\0';
	close(fd);
	return (here_doc);
}

char	*get_limiter(t_cmd *cmd)
{
	while (cmd->redir != NULL)
	{
		if (cmd->redir->type == HERE_DOC)
			return (cmd->redir->file);
		cmd->redir = cmd->redir->next;
	}
	return (NULL);
}
