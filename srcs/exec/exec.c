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

static bool	init_redir_out(t_data *data, t_cmd *cmd)
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
				return (print_err("ERROR: opening FD !\n"));
		}
		if (cmd->redir->type == APPEND)
		{
			cmd->fd_out = open(cmd->redir->file, O_WRONLY | O_CREAT | O_APPEND,
					0644);
			if (cmd->fd_out < 0)
				return (print_err("ERROR: opening FD !\n"));
		}
		cmd->redir = cmd->redir->next;
	}
	return (true);
}

static bool	init_redir_in(t_data *data, t_cmd *cmd)
{
	while (cmd->redir)
	{
		if (cmd->redir->type == REDIR_IN)
		{
			cmd->fd_in = open(cmd->redir->file, O_RDONLY);
			if (cmd->fd_in < 0)
				return (print_err("ERROR: opening FD !\n"));
		}
		if (cmd->redir->type == HERE_DOC)
		{
			cmd->redir->file = heredoc(data, get_limiter(cmd));
			if (cmd->redir->file != NULL)
			{
				cmd->fd_in = open(cmd->redir->file, O_RDONLY);
				if (cmd->fd_in < 0)
					return (print_err("ERROR: opening FD !\n"));
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
	if (init_redir_in(data, data->cmd) || init_redir_out(data, data->cmd))
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
	reset_signal();
	wait_child(last_pid, &data->return_value);
	close_fd(head_cmd);
}
