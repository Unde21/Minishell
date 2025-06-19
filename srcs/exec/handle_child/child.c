#include "exec.h"
#include "parsing.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

static bool	dup_child(t_cmd *cmd)
{
	if (dup2(cmd->fd_in, STDIN_FILENO) == -1)
	{
		close(cmd->fd_in);
		return (print_err_false(ERR_DUP));
	}
	if (dup2(cmd->fd_out, STDOUT_FILENO) == -1)
	{
		close(cmd->fd_out);
		return (print_err_false(ERR_DUP));
	}
	close_fd(cmd, false);
	return (true);
}

static void	free_and_exit(t_data *data, char *path_cmd, t_cmd *head,
		char **params_cpy)
{
	free(path_cmd);
	free_all(data->env_array);
	free_all(params_cpy);
	close_fd(head, true);
	clear_cmd(head);
	free_listed_env(data);
	exit(data->return_value);
}

static void	child_exec(t_data *data, char *path_cmd, char **params_cpy,
		t_cmd *head)
{
	if (dup_child(data->cmd) == false || data->return_value != 0)
		free_and_exit(data, path_cmd, head, params_cpy);
	if (is_builtin(data))
	{
		execute_builtins(data, head);
		free_and_exit(data, path_cmd, head, params_cpy);
	}
	if (path_cmd == NULL)
		free_and_exit(data, path_cmd, head, params_cpy);
	close_fd(head, true);
	clear_cmd(head);
	execve(path_cmd, params_cpy, data->env_array);
	perror(ERR_EXECVE);
	free(path_cmd);
	close(data->cmd->fd_in);
	close(data->cmd->fd_out);
	free_all(params_cpy);
	exit(127);
}

void	child(t_data *data, char *path_cmd, t_cmd *head)
{
	char	**params_cpy;
	int		i;

	params_cpy = malloc(sizeof(char *) * (get_total_length(data->cmd->params)
				+ 1));
	if (params_cpy == NULL)
	{
		data->return_value = 1;
		print_err_false(ERR_MALLOC);
		free_and_exit(data, path_cmd, head, params_cpy);
	}
	i = -1;
	while (data->cmd->params[++i])
	{
		params_cpy[i] = ft_strdup(data->cmd->params[i]);
		if (params_cpy[i] == NULL)
		{
			data->return_value = 1;
			print_err_false(ERR_MALLOC);
			free_and_exit(data, path_cmd, head, params_cpy);
		}
	}
	params_cpy[i] = NULL;
	set_signal_action_child();
	child_exec(data, path_cmd, params_cpy, head);
}

pid_t	init_child(t_data *data, t_cmd *head_cmd, char *path_cmd)
{
	pid_t	last_pid;
	pid_t	pid;

	pid = 0;
	last_pid = 0;
	pid = fork();
	if (pid < 0)
	{
		close_fd(head_cmd, true);
		print_err_false(ERR_FORK);
	}
	else if (pid == 0)
		child(data, path_cmd, head_cmd);
	if (data->cmd->next == NULL)
		last_pid = pid;
	return (last_pid);
}
