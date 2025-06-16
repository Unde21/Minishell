#include "exec.h"
#include "parsing.h"
#include <signal.h>

static void	set_signal_action_child(void)
{
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
				*return_value = 128 + WTERMSIG(status);
		}
	}
}

void	dup_child(t_cmd *cmd)
{
	if (dup2(cmd->fd_in, STDIN_FILENO) == -1)
	{
		close(cmd->fd_in);
		print_err(ERR_DUP);
		exit(1);
	}
	if (dup2(cmd->fd_out, STDOUT_FILENO) == -1)
	{
		close(cmd->fd_out);
		print_err(ERR_DUP);
		exit(1);
	}
	if (cmd->pipe_fd[0] != STDIN_FILENO && cmd->pipe_fd[0] != -1)
		close(cmd->pipe_fd[0]);
	if (cmd->pipe_fd[1] != STDIN_FILENO && cmd->pipe_fd[1] != -1)
		close(cmd->pipe_fd[1]);
}

void	init_child(t_data *data, char *path_cmd, t_cmd *head)
{
	char	**params_cpy;
	int		i;

	params_cpy = malloc(sizeof(char *) * (data->cmd->nb_args + 1));
	i = -1;
	while (data->cmd->params[++i])
		params_cpy[i] = ft_strdup(data->cmd->params[i]);
	params_cpy[i] = NULL;
	set_signal_action_child();
	dup_child(data->cmd);
	close_fd(head);
	if (data->return_value != 0)
		exit(data->return_value);
	if (child_builtin(data))
	{
		free(path_cmd);
		exit(data->return_value);
	}
	clear_cmd(head);
	execve(path_cmd, params_cpy, data->env);
	perror(ERR_EXECVE);
	exit(127);
}
