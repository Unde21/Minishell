#include "builtins.h"
#include "exec.h"
#include <stdlib.h>
#include <unistd.h>

void	close_fd(t_cmd *cmd)
{
	// Faut delete les commentaires ici ?
	while (cmd)
	{
		if (cmd->pipe_fd[0] != -1)
			close(cmd->pipe_fd[0]);
		if (cmd->pipe_fd[1] != -1)
			close(cmd->pipe_fd[1]);
		cmd = cmd->next;
	}
}
