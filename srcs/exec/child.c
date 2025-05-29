#include "exec.h"

void	init_child(t_cmd *cmd, char *path_cmd, char **env)
{
	if (dup2(cmd->fd_in, STDIN_FILENO) == -1)
	{
		close(cmd->fd_in);
		print_err("ERROR: 1 !\n");
		exit(1);
	}
	if (cmd->fd_in != STDIN_FILENO)
		close(cmd->fd_in);
	if (dup2(cmd->fd_out, STDOUT_FILENO) == -1)
	{
		close(cmd->fd_out);
		print_err("ERROR: 2 !\n");
		exit(1);
	}
	if (cmd->fd_out != STDOUT_FILENO)
		close(cmd->fd_out);
	execve(path_cmd, cmd->params, env);
	perror("ERROR: execve failed !\n");
	exit(127);
}
