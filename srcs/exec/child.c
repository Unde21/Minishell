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
		if (WIFEXITED(status))
			*return_value = WEXITSTATUS(status);
	}
}
void	init_child(t_data *data, char *path_cmd, t_cmd *head)
{
	if (dup2(data->cmd->fd_in, STDIN_FILENO) == -1)
	{
		close(data->cmd->fd_in);
		print_err("ERROR: 1 !\n");
		exit(1);
	}
	if (dup2(data->cmd->fd_out, STDOUT_FILENO) == -1)
	{
		close(data->cmd->fd_out);
		print_err("ERROR: 2 !\n");
		exit(1);
	}
	if (data->cmd->pipe_fd[0] != STDIN_FILENO && data->cmd->pipe_fd[0] != -1)
		close(data->cmd->pipe_fd[0]);
	if (data->cmd->pipe_fd[1] != STDIN_FILENO && data->cmd->pipe_fd[1] != -1)
		close(data->cmd->pipe_fd[1]);
	close_fd(head);
	if (data->return_value != 0)
		exit(data->return_value);
	execve(path_cmd, data->cmd->params, data->env);
	perror("ERROR: execve failed !\n");
	exit(127);
}
