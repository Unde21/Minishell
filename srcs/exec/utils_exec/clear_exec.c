#include "builtins.h"
#include "exec.h"



void	close_fd(t_cmd *cmd)
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
// void	clear_exec(t_data *data)
// {
// 	close_fd(data->cmd);
// 	free_listed_env();
// }