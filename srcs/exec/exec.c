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
		print_err(ERR_PIPE);
	}
	if (cmd->fd_out == STDOUT_FILENO)
		cmd->fd_out = cmd->pipe_fd[1];
	if (cmd->next->fd_in == STDIN_FILENO)
		cmd->next->fd_in = cmd->pipe_fd[0];
}

static bool	init_redir(t_data *data, t_cmd *cmd)
{
	while (cmd->redir)
	{
		if (cmd->redir->file == NULL)
		{
			ft_dprintf(2, PRINT_BASH);
			ft_dprintf(2, " %s: ", data->ambiguous_file);
			ft_dprintf(2, ERR_AMBIGUOUS);
			data->return_value = 1;
			return (false);
		}
		if (cmd->redir->type == REDIR_OUT)
		{
			cmd->fd_out = open(cmd->redir->file, O_WRONLY | O_CREAT | O_TRUNC,
					0644);
			if (cmd->fd_out < 0)
				return (print_err(ERR_OP_FD));
		}
		if (cmd->redir->type == APPEND)
		{
			cmd->fd_out = open(cmd->redir->file, O_WRONLY | O_CREAT | O_APPEND,
					0644);
			if (cmd->fd_out < 0)
				return (print_err(ERR_OP_FD));
		}
		if (cmd->redir->type == REDIR_IN)
		{
			cmd->fd_in = open(cmd->redir->file, O_RDONLY);
			if (cmd->fd_in < 0)
				return (print_err(ERR_OP_FD));
		}
		if (cmd->redir->type == HERE_DOC)
		{
			cmd->redir->file = heredoc(data, get_limiter(cmd));
			reset_signal();
			if (cmd->redir->file != NULL)
			{
				cmd->fd_in = open(cmd->redir->file, O_RDONLY);
				if (cmd->fd_in < 0)
					return (print_err(ERR_OP_FD));
				unlink(cmd->redir->file);
				free(cmd->redir->file);
			}
			else
				return (false);
		}
		cmd->redir = cmd->redir->next;
	}
	return (true);
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
						path_cmd))
					*path_cmd = data->cmd->params[0];
			}
			else
				*path_cmd = get_path_cmd(data->cmd->params, *path_cmd,
						return_value);
			if (*path_cmd == NULL)
				print_access_error(data->cmd->params[0]);
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
		data->return_value = 0;
		if (solo_builtin(data) && data->cmd->next == NULL)
			return ;
		init(data, &path_cmd, &data->return_value);
		if (data->return_value == 0 && g_return_value == 0)
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
		data->cmd = data->cmd->next;
	}
	reset_signal();
	close_fd(head_cmd);
	wait_child(last_pid, &data->return_value);
}
