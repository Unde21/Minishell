#include "exec.h"
#include "parsing.h"
#include <unistd.h>
#include <stdlib.h>

static bool	dup_child(t_cmd *cmd)
{
	if (dup2(cmd->fd_in, STDIN_FILENO) == -1)
	{
		close(cmd->fd_in);
		return (print_err(ERR_DUP));
	}
	if (dup2(cmd->fd_out, STDOUT_FILENO) == -1)
	{
		close(cmd->fd_out);
		return (print_err(ERR_DUP));
	}

	return (true);
}

static void	free_and_exit(t_data *data, char *path_cmd, t_cmd *head,
		char **params_cpy)
{
	free(path_cmd);
	free_all(params_cpy);
	close_fd(head);
	clear_cmd(data->cmd);
	exit(data->return_value);
}

static void	child_exec(t_data *data, char *path_cmd, char **params_cpy,
		t_cmd *head)
{
	if (dup_child(data->cmd) == false || data->return_value != 0)
		free_and_exit(data, path_cmd, head, params_cpy);
	if (is_builtin(data))
	{
		execute_builtins(data);
		free_and_exit(data, path_cmd, head, params_cpy);
	}
	if (path_cmd == NULL)
		free_and_exit(data, path_cmd, head, params_cpy);
	close_fd(head);
	execve(path_cmd, params_cpy, data->env_array);
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
