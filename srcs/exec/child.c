#include "exec.h"

void	wait_child(int *return_value)
{
	pid_t	end_pid;
	int		status;

	status = 0;
	while (1)
	{
		end_pid = wait(&status);
		if (end_pid < 0)
			break ;
		*return_value = WEXITSTATUS(status);
	}
}
void	init_child(t_cmd *cmd, char *path_cmd, char **env, t_cmd *head)
{
	if (dup2(cmd->fd_in, STDIN_FILENO) == -1)
	{
		close(cmd->fd_in);
		print_err("ERROR: 1 !\n");
		exit(1);
	}
	if (dup2(cmd->fd_out, STDOUT_FILENO) == -1)
	{
		close(cmd->fd_out);
		print_err("ERROR: 2 !\n");
		exit(1);
	}
	if (cmd->pipe_fd[0] != STDIN_FILENO && cmd->pipe_fd[0] != -1)
		close(cmd->pipe_fd[0]);
	if (cmd->pipe_fd[1] != STDIN_FILENO && cmd->pipe_fd[1] != -1)
		close(cmd->pipe_fd[1]);
	close_fd(head);
	execve(path_cmd, cmd->params, env);
	perror("ERROR: execve failed !\n");
	exit(127);
}
