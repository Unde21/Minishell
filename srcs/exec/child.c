#include "exec.h"

void	wait_child(pid_t last_pid, int *return_value)
{
	pid_t	pid;
	int		status;

	while ((pid = waitpid(-1, &status, 0)) > 0)
	{
		if (pid == last_pid)
		{
			if (WIFEXITED(status))
				*return_value = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				*return_value = 128 + WTERMSIG(status);
		}
	}
}

void	dup_child(t_cmd *cmd)
{
	if (dup2(cmd->fd_in, STDIN_FILENO) == -1)
	{
		close(cmd->fd_in);
		print_err("ERROR: dup child stdin !\n");
		exit(1);
	}
	if (dup2(cmd->fd_out, STDOUT_FILENO) == -1)
	{
		close(cmd->fd_out);
		print_err("ERROR: dup child stdout !\n");
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
	if (child_builtin(data))
		exit(data->return_value);
	execve(path_cmd, data->cmd->params, data->env);
	perror("ERROR: execve failed !\n");
	exit(127);
}
