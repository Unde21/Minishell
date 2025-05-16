#include "exec.h"
#include "parsing.h"

// void	executable(t_data *data)
// {
// 	int	i;

// 	i = -1;
// 	while (data->cmd)
// 	{
// 		while (data->cmd->args[++i].content)
// 		{
// 			if (is_cmd(data, data->cmd->args[i].content))
// 				printf("executable => %s\n", data->cmd->args[i].content);
// 			else
// 				print_err(ERR_CMD);
// 		}
// 		if (is_heredoc(data))
// 			heredoc(get_limiter(data));
// 		if (is_redir(data) == 1)
// 			printf("%s => redirection in\n", data->cmd->args->content);
// 		else if (is_redir(data) == 2)
// 			printf("%s => redirection out\n", data->cmd->args->content);
// 		i = -1;
// 		if (data->cmd->next != NULL)
// 			printf("there_is_pipe\n");
// 		data->cmd = data->cmd->next;
// 	}
// }

static void	close_pipefd(t_data *data, int pipe_fd[])
{
	int	i;

	i = -1;
	while (++i < (data->nb_cmd - 1))
		close(pipe_fd[i]);
}

bool	exec_init(t_data *data)
{
	pid_t	pid;
	int		status;
	int		i;
	int		pipe_fd[2];

	status = 0;
	i = -1;
	while (++i < data->nb_cmd)
	{
		if (data->cmd->next != NULL)
			if (pipe(pipe_fd) < 0)
				return (print_err("ERROR: pipe failed !\n"));
		pid = fork();
		if (pid < 0)
		{
			close_pipefd(data, pipe_fd);
			return (print_err("ERROR: fork failed !\n"));
		}
		else if (pid > 0)
			child_init(data, pipe_fd, i);
	}
	waitpid(pid, &status, 0);
	free_listed_env(data);
	close_pipefd(data, pipe_fd);
	return (true);
}
