#include "builtins.h"
#include "exec.h"
#include <stdlib.h>
#include <unistd.h>

static void	close_and_free_all(t_data *data, t_cmd *head)
{
	if (data->cmd->fd_in != STDIN_FILENO && data->cmd->fd_in != -1)
		close(data->cmd->fd_in);
	if (data->cmd->fd_out != STDOUT_FILENO && data->cmd->fd_out != -1)
		close(data->cmd->fd_out);
	if (data->save_stdin != -1)
		close(data->save_stdin);
	if (data->save_stdout != -1)
		close(data->save_stdout);
	data->save_stdin = -1;
	data->save_stdout = -1;
	close_fd(head, true);
	free_all(data->env_array);
	clear_cmd(head);
	free_listed_env(data);
}

static void	is_number(t_data *data, char *s, t_cmd *head)
{
	size_t	i;

	i = 0;
	if (s == NULL)
		return ;
	while (s[i])
	{
		if (ft_isdigit(s[i]) == 0)
		{
			ft_dprintf(STDERR_FILENO, "%s%s%s", EXIT_ERROR, s, ERR_NUM_ARG);
			close_and_free_all(data, head);
			exit(2);
		}
		++i;
	}
}

static void	get_exit_code(t_data *data, char *s, t_cmd *head)
{
	int	exit_code;
	int	check_error;

	check_error = 0;
	if (s == NULL)
		exit_code = data->return_value;
	else
		exit_code = ft_atoll(s, &check_error) % 256;
	if (check_error != 0)
	{
		ft_dprintf(STDERR_FILENO, "%s%s%s", EXIT_ERROR, s, ERR_NUM_ARG);
		close_and_free_all(data, head);
		exit(2);
	}
	close_and_free_all(data, head);
	exit(exit_code);
}

int	ft_exit(t_data *data, t_cmd *cmd, t_cmd *head)
{
	char	*s;
	int		exit_code;

	exit_code = 0;
	if (cmd->nb_args == 1)
	{
		exit_code = data->return_value;
		close_and_free_all(data, head);
		exit(exit_code);
	}
	else
		s = cmd->params[1];
	is_number(data, s, head);
	if (cmd->nb_args > 2)
	{
		ft_dprintf(STDERR_FILENO, EXIT_TOO_MANY);
		data->return_value = 1;
		return (-1);
	}
	get_exit_code(data, s, head);
	return (0);
}
