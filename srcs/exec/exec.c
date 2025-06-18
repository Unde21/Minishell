#include "builtins.h"
#include "exec.h"
#include "parsing.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

static void	set_pipe(t_cmd *cmd, t_data *data)
{
	t_cmd	*head;

	head = cmd;
	if (pipe(cmd->pipe_fd) < 0)
	{
		close_fd(head, true);
		data->return_value = 1;
		print_err_false(ERR_CREAT_PIPE);
	}
	if (cmd->fd_out == STDOUT_FILENO)
		cmd->fd_out = cmd->pipe_fd[1];
	if (cmd->next->fd_in == STDIN_FILENO)
		cmd->next->fd_in = cmd->pipe_fd[0];
}

static void	get_absolute_path(t_data *data, char **path_cmd, int *return_value)
{
	if (data->cmd->params[0] && g_return_value == 0)
	{
		if (data->env[0] == NULL || ft_strchr(data->cmd->params[0],
				'/') != NULL)
		{
			if (is_access_ok(data->cmd->params[0], data->cmd->params, data))
			{
				*path_cmd = ft_strdup(data->cmd->params[0]);
				if (*path_cmd == NULL)
					*return_value = 1;
			}
		}
		else
			*path_cmd = get_path_cmd(data, data->cmd->params);
		if (*path_cmd == NULL)
			print_access_error(data->cmd->params[0], data);
	}
}

static bool	dup_parent_builtins(t_data *data, t_cmd *cmd)
{
	int	save_stdin;
	int	save_stdout;

	save_stdin = dup(STDIN_FILENO);
	save_stdout = dup(STDOUT_FILENO);
	data->return_value = 0;
	if (dup2(cmd->fd_in, STDIN_FILENO) == -1)
		return (err_dup_parent(data, cmd, save_stdin, save_stdout));
	if (dup2(cmd->fd_out, STDOUT_FILENO) == -1)
		return (err_dup_parent(data, cmd, save_stdin, save_stdout));
	execute_builtins(data);
	if (dup2(save_stdin, STDIN_FILENO) == -1)
		return (err_dup_parent(data, cmd, save_stdin, save_stdout));
	if (dup2(save_stdout, STDOUT_FILENO) == -1)
		return (err_dup_parent(data, cmd, save_stdin, save_stdout));
	close(save_stdin);
	close(save_stdout);
	return (true);
}

static bool	exec_loop(t_data *data, t_cmd *head_cmd, char *path_cmd,
		pid_t *last_pid)
{
	data->return_value = 0;
	if (data->cmd->next != NULL)
	{
		set_pipe(data->cmd, data);
		if (data->return_value != 0)
			return (false);
	}
	if (init_redir(data, data->cmd) == false)
		return (false);
	if (data->size_cmd == 1 && is_builtin(data))
	{
		dup_parent_builtins(data, data->cmd);
		if (data->cmd->fd_in != STDIN_FILENO && data->cmd->fd_in != -1)
			close(data->cmd->fd_in);
		if (data->cmd->fd_out != STDOUT_FILENO && data->cmd->fd_out != -1)
			close(data->cmd->fd_out);
		data->cmd = head_cmd;
		return (true);
	}
	if (!is_builtin(data))
		get_absolute_path(data, &path_cmd, &data->return_value);
	*last_pid = init_child(data, head_cmd, path_cmd);
	close_fd(data->cmd, false);
	free(path_cmd);
	return (true);
}

void	exec(t_data *data)
{
	char	*path_cmd;
	t_cmd	*head_cmd;
	pid_t	last_pid;

	head_cmd = data->cmd;
	path_cmd = NULL;
	data->size_cmd = get_size_cmd(data->cmd);
	data->env_array = listed_env_to_array(data, data->listed_env);
	if (data->env_array == NULL)
	{
		print_err_false(ERR_MALLOC);
		data->return_value = 1;
		return ;
	}
	while (data->cmd)
	{
		if (exec_loop(data, head_cmd, path_cmd, &last_pid) == false)
			break ;
		data->cmd = data->cmd->next;
	}
	data->cmd = head_cmd;
	reset_signal();
	close_fd(head_cmd, true);
	free_all(data->env_array);
	wait_child(last_pid, &data->return_value);
}
