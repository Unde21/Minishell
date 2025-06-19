/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samaouch <samaouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 01:30:20 by samaouch          #+#    #+#             */
/*   Updated: 2025/06/20 01:30:21 by samaouch         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "exec.h"
#include <stdlib.h>
#include <unistd.h>

void	close_fd(t_cmd *cmd, bool close_all_cmd)
{
	if (close_all_cmd == true)
	{
		while (cmd)
		{
			if (cmd->pipe_fd[0] != -1)
				close(cmd->pipe_fd[0]);
			if (cmd->pipe_fd[1] != -1)
				close(cmd->pipe_fd[1]);
			cmd = cmd->next;
		}
	}
	else if (close_all_cmd == false)
	{
		if (cmd->fd_in != STDIN_FILENO && cmd->fd_in != -1)
			close(cmd->fd_in);
		if (cmd->fd_out != STDOUT_FILENO && cmd->fd_out != -1)
			close(cmd->fd_out);
	}
}
