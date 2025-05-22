#include "exec.h"

bool	first_child(t_data *data, int *pipe_fd)
{
	char	*redir;
	int		fd;
	char	*path;

	redir = wich_redir(data->cmd);
	path = path_cmd(data);
	if ((fd = open(redir, O_RDONLY)) == -1)
		return (close_pipefd(data, pipe_fd));
	if (dup2(fd, STDIN_FILENO) == -1)
		return (print_err("ERROR: dup failed !\n"));
	if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
		return (print_err("ERROR: dup failed !\n"));
	close_pipefd(data, pipe_fd);
	execve(path, cmd, data->env);
	return (true);
}
// bool	middle_child(t_cmd *cmd, int *pipe_fd)
// {
// }
// bool	last_child(t_cmd *cmd, int *pipe_fd)
// {
// }

bool	child_init(t_data *data, int *pipe_fd, int i)
{
	while (data->cmd != NULL)
	{
		if (i == 1)
			return (first_child(data, pipe_fd));
		// else if (data->cmd->next != NULL && data->nb_cmd > 1 && i > 1)
		// 	return (middle_childs(data->cmd, pipe_fd));
		// else if (data->cmd->next == NULL && data->nb_cmd > 1  && i > 1)
		// 	return (last_child(data->cmd, pipe_fd));
		data->cmd = data->cmd->next;
	}
	return (true);
}
