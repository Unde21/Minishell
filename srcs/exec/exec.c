#include "builtins.h"
#include "exec.h"
#include "parsing.h"

void	close_fd(t_cmd *cmd)
{
	while (cmd)
	{
		if (cmd->pipe_fd[0] != -1)
			close(cmd->pipe_fd[0]);
		if (cmd->pipe_fd[1] != -1)
			close(cmd->pipe_fd[1]);
		cmd = cmd->next;
	}
}

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

static bool	init_redir(t_data *data, t_cmd *cmd)
{
	while (cmd->redir)
	{
		if (cmd->redir->file == NULL)
		{
			ft_dprintf(2, PRINT_BASH);
			write(2, " ", 1);
			ft_dprintf(2, ERR_AMBIGUOUS);
			data->return_value = 1;
			return (false);
		}
		if (cmd->redir->type == REDIR_IN)
		{
			cmd->fd_in = open(cmd->redir->file, O_RDONLY);
			if (cmd->fd_in < 0)
				return (print_err("ERROR: opening FD !\n"));
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
		if (cmd->redir->type == HERE_DOC)
		{
			cmd->redir->file = heredoc(data, get_limiter(cmd));
			cmd->fd_in = open(cmd->redir->file, O_RDONLY);
			if (cmd->fd_in < 0)
				return (print_err("ERROR: opening FD !\n"));
			unlink(cmd->redir->file);
			free(cmd->redir->file);
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
		return ;
}

void	exec_init(t_data *data)
{
	char	*path_cmd;
	t_cmd	*head_cmd;
	pid_t	pid;

	head_cmd = data->cmd;
	path_cmd = NULL;
	if (solo_builtin(data) && data->cmd->next == NULL)
		return ;
	while (data->cmd)
	{
		init(data, &path_cmd, &data->return_value);
		pid = fork();
		if (pid < 0)
		{
			close_fd(head_cmd);
			print_err("ERROR: fork failed !\n");
		}
		else if (pid == 0)
			init_child(data, path_cmd, head_cmd);
		data->cmd = data->cmd->next;
	}
	close_fd(head_cmd);
	wait_child(&data->return_value);
}
