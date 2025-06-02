#include "exec.h"

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

static void	init_redir(t_cmd *cmd)
{
	while (cmd->redir)
	{
		if (cmd->redir->type == REDIR_IN)
			if ((cmd->fd_in = open(cmd->redir->file, O_RDONLY)) < 0)
				print_err("ERROR: opening FD !\n");
		if (cmd->redir->type == REDIR_OUT)
			if ((cmd->fd_out = open(cmd->redir->file,
						O_WRONLY | O_CREAT | O_TRUNC, 0644)) < 0)
				print_err("ERROR: opening FD !\n");
		if (cmd->redir->type == APPEND)
			if (((cmd->fd_out = open(cmd->redir->file,
							O_WRONLY | O_CREAT | O_APPEND, 0644))) < 0)
				print_err("ERROR: opening FD !\n");
		if (cmd->redir->type == HERE_DOC)
		{
			cmd->redir->file = heredoc(get_limiter(cmd));
			if ((cmd->fd_in = open(cmd->redir->file, O_RDONLY)) < 0)
				print_err("ERROR: opening FD !\n");
			unlink(cmd->redir->file);
		}
		cmd->redir = cmd->redir->next;
	}
}

void	init(t_cmd *cmd, char **path_cmd, int *return_value)
{
	if (cmd->next != NULL)
		set_pipe(cmd);
	init_redir(cmd);
	get_path_cmd(cmd->params, path_cmd, return_value);
}

void	exec_init(t_data *data)
{
	char	*path_cmd;
	t_cmd	*head_cmd;
	pid_t	pid;

	head_cmd = data->cmd;
	path_cmd = NULL;
	while (data->cmd)
	{
		init(data->cmd, &path_cmd, &data->return_value);
		if (path_cmd == NULL)
			pid = fork();
		if (pid < 0)
		{
			close_fd(head_cmd);
			print_err("ERROR: fork failed !\n");
		}
		else if (pid == 0)
			init_child(data->cmd, path_cmd, data->env, head_cmd);
		data->cmd = data->cmd->next;
	}
	close_fd(head_cmd);
	wait_child(&data->return_value);
}
