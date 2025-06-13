#include "builtins.h"
#include "exec.h"
#include "parsing.h"

static void	set_pipe(t_cmd *cmd)
{
	t_cmd	*head;

	head = cmd;
	if (pipe(cmd->pipe_fd) < 0)
	{
		close_fd(head);
		print_err("ERROR: pipe failed !\n");
	}
	if (cmd->fd_out == STDOUT_FILENO)
		cmd->fd_out = cmd->pipe_fd[1];
	if (cmd->next->fd_in == STDIN_FILENO)
		cmd->next->fd_in = cmd->pipe_fd[0];
}

void	init(t_data *data, char **path_cmd, int *return_value)
{
	if (data->cmd->next != NULL)
		set_pipe(data->cmd);
	if (init_redir(data, data->cmd))
	{
		if (data->cmd->params[0])
		{
			if (data->env[0] == NULL || data->cmd->params[0][0] == '/')
			{
				if (is_access_ok(data->cmd->params[0], &data->return_value,
						path_cmd))
					*path_cmd = data->cmd->params[0];
				else
					return ;
			}
			else
				*path_cmd = get_path_cmd(data->cmd->params, *path_cmd,
						return_value);
		}
	}
	else
	{
		*return_value = 1;
		return ;
	}
}

void	exec_init(t_data *data)
{
	char	*path_cmd;
	t_cmd	*head_cmd;
	pid_t	last_pid;
	pid_t	pid;

	head_cmd = data->cmd;
	path_cmd = NULL;
	if (solo_builtin(data) && data->cmd->next == NULL)
		return ;
	while (data->cmd)
	{
		data->return_value = 0;
		init(data, &path_cmd, &data->return_value);
		if (data->return_value == 0)
		{
			pid = fork();
			if (pid < 0)
			{
				close_fd(head_cmd);
				print_err("ERROR: fork failed !\n");
			}
			else if (pid == 0)
				init_child(data, path_cmd, head_cmd);
			if (data->cmd->next == NULL)
				last_pid = pid;
		}
		data->cmd = data->cmd->next;
	}
	close_fd(head_cmd);
	wait_child(last_pid, &data->return_value);
}
