#include "exec.h"

bool	first_child(t_data *data, int *pipe_fd)
{
	char	*redir;
	int		fd;

	redir = wich_redir(data->cmd);
	if (redir == NULL)
		fd = open(STDIN_FILENO, O_RDONLY);
	else
		fd = open(redir, O_RDONLY);
	if (fd == -1)
		return (close_pipefd(data, pipe_fd));
	if (dup2(fd, STDIN_FILENO) == -1)
		return (print_err("ERROR: dup failed !\n"));
	if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
		return (print_err("ERROR: dup failed !\n"));
	close_pipefd(data, pipe_fd);
	return (true);
}
bool	middle_child(t_cmd *cmd, int *pipe_fd)
{
}
bool	last_child(t_cmd *cmd, int *pipe_fd)
{
}

bool	child_init(t_data *data, int pipe_fd)
{
	char	*redir;

	while (data->cmd != NULL)
	{
		if (data->nb_cmd == 1)
			return (first_child(data->cmd, pipe_fd));
		else if (data->cmd->next != NULL && data->nb_cmd > 1)
			return (middle_childs(data->cmd, pipe_fd));
		else if (data->cmd->next == NULL && data->nb_cmd > 1)
			return (last_child(data->cmd, pipe_fd));
		data->cmd = data->cmd->next;
	}
	return (true);
}
