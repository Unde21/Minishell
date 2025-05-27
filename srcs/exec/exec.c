#include "exec.h"

void	close_fd(t_cmd *cmd)
{
	while (cmd)
	{
		if (cmd->pipe_fd_current[0] != -1)
			close(cmd->pipe_fd_current[0]);
		if (cmd->pipe_fd_current[1] != -1)
			close(cmd->pipe_fd_current[1]);
		cmd = cmd->next;
	}
}

bool	init_pipe(t_cmd *cmd)
{
	while (cmd && cmd->next != NULL)
	{
		(cmd)->pipe_fd_current[0] = -1;
		(cmd)->pipe_fd_current[1] = -1;
		if (pipe(cmd->pipe_fd_current) < 0)
		{
			close_fd(cmd);
			return (print_err("ERROR: pipe failed !\n"));
		}
		cmd = cmd->next;
	}
	return (true);
}

void	set_pipe(t_cmd *cmd)
{
	if (cmd->next != NULL)
	{
		cmd->fd_out = cmd->pipe_fd_current[1];
		cmd->next->fd_in = cmd->pipe_fd_current[0];
	}
}

bool	init_redir(t_cmd *cmd)
{
	(cmd)->fd_in = 0;
	(cmd)->fd_out = 1;
	while (cmd->redir)
	{
		if (cmd->redir->type == REDIR_IN)
			cmd->fd_in = open(cmd->redir->file, O_RDONLY);
		else if (cmd->redir->type == REDIR_OUT)
			cmd->fd_out = open(cmd->redir->file, O_WRONLY | O_CREAT | O_TRUNC,
					0644);
		else if (cmd->redir->type == APPEND)
			cmd->fd_out = open(cmd->redir->file, O_WRONLY | O_CREAT | O_APPEND,
					0644);
		else if (cmd->redir->type == HERE_DOC)
		{
			cmd->redir->file = heredoc(get_limiter(cmd));
			cmd->fd_in = open(cmd->redir->file, O_RDONLY);
			unlink(cmd->redir->file);
		}
		cmd->redir = cmd->redir->next;
	}
	return (true);
}

bool	exec_init(t_data *data)
{
	int		status;
	char	*path_cmd;
	pid_t	pid;

	path_cmd = NULL;
	while (data->cmd)
	{
		path_cmd = get_path_cmd(data->cmd->params);
		init_pipe(data->cmd);
		set_pipe(data->cmd);
		init_redir(data->cmd);
		pid = fork();
		if (pid < 0)
		{
			close_fd(data->cmd);
			return (print_err("ERROR: fork failed !\n"));
		}
		else if (pid == 0)
			init_child(data->cmd, path_cmd, data->env);
		data->cmd = data->cmd->next;
	}
	while (wait(&status) > 0)
		;
	close_fd(data->cmd);
	return (true);
}
