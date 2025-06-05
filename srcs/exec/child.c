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
		else if (WIFSIGNALED(status))
			*return_value = WIFSTOPPED(status);
	}
}

void	dup_child(t_cmd *cmd)
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
}

void	init_child(t_data *data, char *path_cmd, t_cmd *head)
{
	dup_child(data->cmd);
	close_fd(head);
	if (data->return_value != 0)
		exit(data->return_value);
	if (is_child_builtin(data->cmd->params) == true)
	{
		child_builtin(data);
		exit(data->return_value);
	}
	execve(path_cmd, data->cmd->params, data->env);
	perror("ERROR: execve failed !\n");
	exit(127);
}
