#include "exec.h"
#include "parsing.h"
#include <unistd.h>
#include <stdlib.h>

static bool	dup_child(t_cmd *cmd)
{
<<<<<<< HEAD
	if (dup2(cmd->fd_in, STDIN_FILENO) == -1)
=======
	struct sigaction	sa;

	ft_bzero(&sa, sizeof(sa));
	sa.sa_handler = SIG_DFL;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

void	wait_child(pid_t last_pid, int *return_value)
{
	pid_t	pid;
	int		status;

	while (1)
	{
		pid = waitpid(-1, &status, 0);
		if (pid < 0)
			break ;
		else if (pid == last_pid)
		{
			if (WIFEXITED(status))
				*return_value = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
			{
				*return_value = 128 + WTERMSIG(status);
				if (*return_value == 131)
					ft_dprintf(STDOUT_FILENO, QUIT);
			}
		}
	}
}

void	dup_child(t_cmd *cmd)
{
	if (dup2(cmd->fd_in, STDIN_FILENO) == -1)
	// faut free de trucs avant de exit
>>>>>>> origin/norm_leak
	{
		close(cmd->fd_in);
		return (print_err(ERR_DUP));
	}
	if (dup2(cmd->fd_out, STDOUT_FILENO) == -1)
<<<<<<< HEAD
=======
	// faut free de trucs avant de exit
>>>>>>> origin/norm_leak
	{
		close(cmd->fd_out);
		return (print_err(ERR_DUP));
	}
	if (cmd->pipe_fd[0] != STDIN_FILENO && cmd->pipe_fd[0] != -1)
		close(cmd->pipe_fd[0]);
	if (cmd->pipe_fd[1] != STDIN_FILENO && cmd->pipe_fd[1] != -1)
		close(cmd->pipe_fd[1]);
	return (true);
}

<<<<<<< HEAD
static void	free_and_exit(t_data *data, char *path_cmd, t_cmd *head,
		char **params_cpy)
=======
void	init_child(char **env_array, t_data *data, char *path_cmd, t_cmd *head)
>>>>>>> origin/norm_leak
{
	free(path_cmd);
	free_all(params_cpy);
	close_fd(head);
	clear_cmd(data->cmd);
	exit(data->return_value);
}

<<<<<<< HEAD
static void	child_exec(t_data *data, char *path_cmd, char **params_cpy,
		t_cmd *head)
{
	if (dup_child(data->cmd) == false || data->return_value != 0)
		free_and_exit(data, path_cmd, head, params_cpy);
=======
	i = 0;
	while (data->cmd->params[i])
		++i;
	params_cpy = malloc(sizeof(char *) * (i + 1)); // secure
	if (!params_cpy)
		return ;
	params_cpy[i] = NULL;
	i = -1;
	while (data->cmd->params[++i])
		params_cpy[i] = ft_strdup(data->cmd->params[i]);
	set_signal_action_child();
	dup_child(data->cmd);
	if (data->return_value != 0)
	{
		free(path_cmd);
		free_all(params_cpy);
		exit(data->return_value);
	}
>>>>>>> origin/norm_leak
	if (child_builtin(data))
		free_and_exit(data, path_cmd, head, params_cpy);
	close_fd(head);
	execve(path_cmd, params_cpy, env_array);
	perror(ERR_EXECVE);
	free(path_cmd);
	free_all(params_cpy);
	clear_cmd(data->cmd);
	exit(127);
}

void	init_child(t_data *data, char *path_cmd, t_cmd *head)
{
	char	**params_cpy;
	int		i;

	params_cpy = malloc(sizeof(char *) * (get_total_length(data->cmd->params)
				+ 1));
	if (params_cpy == NULL)
	{
		data->return_value = 1;
		print_err(ERR_MALLOC);
		free_and_exit(data, path_cmd, head, params_cpy);
	}
	i = -1;
	while (data->cmd->params[++i])
	{
		params_cpy[i] = ft_strdup(data->cmd->params[i]);
		if (params_cpy[i] == NULL)
		{
			data->return_value = 1;
			print_err(ERR_MALLOC);
			free_and_exit(data, path_cmd, head, params_cpy);
		}
	}
	params_cpy[i] = NULL;
	set_signal_action_child();
	child_exec(data, path_cmd, params_cpy, head);
}
