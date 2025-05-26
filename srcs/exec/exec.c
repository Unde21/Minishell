#include "exec.h"

bool	close_fd(int *pipe_fd)
{
	int	i;

	i = -1;
	while (pipe_fd[++i] != -1)
		close(pipe_fd[i]);
	return (true);
}

char	*get_path_cmd(char **params)
{
	int		i;
	char	**path;

	i = -1;
	path = ft_split(getenv("PATH"), ':');
	if (!path)
	{
		print_err("malloc failed\n");
		return (NULL);
	}
	while (path[++i])
	{
		path[i] = ft_strjoin(path[i], "/");
		path[i] = ft_strjoin(path[i], params[0]);
		if (access(path[i], X_OK) == 0)
			return (path[i]);
	}
	i = -1;
	while (path[++i])
		free(path[i]);
	free(path);
	return (NULL);
}

bool	init_pipe(t_cmd *cmd, int *pipe_fd)
{
	(cmd)->fd_in = 0;
	(cmd)->fd_out = 1;
	if (cmd->next != NULL)
		if (pipe(pipe_fd) < 0)
			return (print_err("ERROR: pipe failed !\n"));
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
	int		pipe_fd[2] = {-1, -1};
	int		status;
	char	*path_cmd;
	pid_t	pid;

	path_cmd = NULL;
	while (data->cmd)
	{
		path_cmd = get_path_cmd(data->cmd->params);
		init_pipe(data->cmd, pipe_fd);
		pid = fork();
		if (pid < 0)
		{
			close_fd(pipe_fd);
			return (print_err("ERROR: fork failed !\n"));
		}
		else if (pid == 0)
			init_child(data->cmd, path_cmd, pipe_fd, data->env);
		data->cmd = data->cmd->next;
	}
	while (wait(&status) > 0)
		;
	close_fd(pipe_fd);
	return (true);
}
