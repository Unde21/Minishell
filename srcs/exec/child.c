#include "exec.h"

bool	init_child(t_cmd *cmd, char *path_cmd, int *pipe_fd, char **env)
{
	if (dup2(cmd->fd_in, STDIN_FILENO) == -1)
		return (print_err("ERROR: 1 !\n"));
	if (dup2(cmd->fd_out, STDOUT_FILENO) == -1)
		return (print_err("ERROR: 2 !\n"));
	close_fd(pipe_fd);
	execve(path_cmd, cmd->params, env);
	return (print_err("ERROR: execve failed!\n"));
}
