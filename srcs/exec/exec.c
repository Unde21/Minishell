#include "builtins.h"
#include "exec.h"
#include "parsing.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

static void	set_pipe(t_cmd *cmd)
{
	t_cmd	*head;

	head = cmd;
	if (pipe(cmd->pipe_fd) < 0)
	{
		close_fd(head);
		print_err(ERR_PIPE);
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
		if (data->cmd->params[0] && g_return_value == 0)
		{
			if (data->env[0] == NULL || ft_strchr(data->cmd->params[0],
					'/') != NULL)
			{
				if (is_access_ok(data->cmd->params[0], &data->return_value,
						data->cmd->params))
				{
					*path_cmd = ft_strdup(data->cmd->params[0]);
					if (*path_cmd == NULL)
						*return_value = 1;
				}
			}
			else
				*path_cmd = get_path_cmd(data, data->cmd->params, return_value);
			if (*path_cmd == NULL)
				print_access_error(data->cmd->params[0], data);
		}
		return ;
	}
	*return_value = 1;
}

void	exec_init(t_data *data)
{
	char	*path_cmd;
	t_cmd	*head_cmd;
	pid_t	last_pid;
	pid_t	pid;

	head_cmd = data->cmd;
	path_cmd = NULL;
	while (data->cmd)
	{
		data->env_array = listed_env_to_array(data, data->listed_env);
		init(data, &path_cmd, &data->return_value);
		if (data->cmd->next == NULL && data->return_value == 0
			&& is_builtin(data))
		{
			data->cmd = head_cmd;
			return ;
		}
		if (data->return_value == 0 && path_cmd != NULL)
		{
			pid = fork();
			if (pid < 0)
			{
				close_fd(head_cmd);
				print_err(ERR_FORK);
			}
			else if (pid == 0 && path_cmd != NULL)
				init_child(data, path_cmd, head_cmd);
			if (data->cmd->next == NULL)
				last_pid = pid;
		}
		free(path_cmd);
		data->cmd = data->cmd->next;
	}
	data->cmd = head_cmd;
	reset_signal();
	close_fd(head_cmd);
	wait_child(last_pid, &data->return_value);
}
