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
}

bool	err_dup_parent(t_data *data, t_cmd *cmd, int save_stdin, int save_stdout)
{
	if (save_stdin != -1)
		close(save_stdin);
	if (save_stdout != -1)
		close(save_stdout);
	if (cmd->fd_in != -1)
		close(cmd->fd_in);
	if (cmd->fd_out != -1)
	close(cmd->fd_out);
	print_err(ERR_DUP);
	data->return_value = 1;
	return (false);
}

static bool dup_parent_builtins(t_data *data, t_cmd *cmd)
{
	int	save_stdin;
	int	save_stdout;

	save_stdin = dup(STDIN_FILENO);
	save_stdout = dup(STDOUT_FILENO);

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

void	exec_init(t_data *data)
{
	char	*path_cmd;
	t_cmd	*head_cmd;
	pid_t	last_pid;
	pid_t	pid;

	head_cmd = data->cmd;
	path_cmd = NULL;
	data->env_array = listed_env_to_array(data, data->listed_env);
	if (data->env_array == NULL)
	{
		print_err(ERR_MALLOC);
		data->return_value = 1;
		return ;
	}
	while (data->cmd)
	{
		if (data->cmd->next != NULL)
			set_pipe(data->cmd);
		if (init_redir(data, data->cmd) == false)
			break ;
		if (data->cmd->next == NULL && data->return_value == 0
			&& is_builtin(data))
			{
				dup_parent_builtins(data, data->cmd);
				if (data->cmd->fd_in != STDIN_FILENO && data->cmd->fd_in != -1)
					close(data->cmd->fd_in);
				if (data->cmd->fd_out != STDOUT_FILENO && data->cmd->fd_out != -1)
					close(data->cmd->fd_out);
				data->cmd = head_cmd;
				return ;
			}
		if (!is_builtin(data))
			init(data, &path_cmd, &data->return_value);
		if (data->return_value == 0)
		{
			pid = fork();
			if (pid < 0)
			{
				close_fd(head_cmd);
				print_err(ERR_FORK);
			}
			else if (pid == 0)
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
	free_all(data->env_array);
	wait_child(last_pid, &data->return_value);
}
