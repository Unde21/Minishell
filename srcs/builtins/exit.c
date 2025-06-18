#include "builtins.h"
#include <stdlib.h>
#include <unistd.h>
#include "exec.h"

static void	is_number(t_data *data, char *s)
{
	size_t	i;

	i = 0;
	if (s == NULL)
		return ;
	while (s[i])
	{
		if (ft_isdigit(s[i]) == 0)
		{
			ft_dprintf(STDERR_FILENO, EXIT_ERROR);
			ft_dprintf(STDERR_FILENO, "%s", s);
			ft_dprintf(STDERR_FILENO, ERR_NUM_ARG);
			if (data->cmd->fd_in != STDIN_FILENO && data->cmd->fd_in != -1)
				close(data->cmd->fd_in);
			if (data->cmd->fd_out != STDOUT_FILENO && data->cmd->fd_out != -1)
				close(data->cmd->fd_out);
			close_fd(data->cmd);
			exit(2);
		}
		++i;
	}
}

static void	get_exit_code(t_data *data, char *s)
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
		ft_dprintf(STDERR_FILENO, EXIT_ERROR);
		ft_dprintf(STDERR_FILENO, "%s", s);
		ft_dprintf(STDERR_FILENO, ERR_NUM_ARG);
		exit(2);
	}
	if (data->cmd->fd_in != STDIN_FILENO && data->cmd->fd_in != -1)
		close(data->cmd->fd_in);
	if (data->cmd->fd_out != STDOUT_FILENO && data->cmd->fd_out != -1)
		close(data->cmd->fd_out);
	close_fd(data->cmd);
	exit(exit_code);
}

int	ft_exit(t_data *data, t_cmd *cmd)
{
	char	*s;
	int		exit_code;

	exit_code = 0;
	if (cmd->nb_args == 1)
	{
		exit_code = data->return_value;
		close_fd(cmd);
		exit(exit_code);
	}
	else
		s = cmd->params[1];
	is_number(data, s);
	if (cmd->nb_args > 2)
	{
		ft_dprintf(STDERR_FILENO, EXIT_TOO_MANY);
		data->return_value = 1;
		return (-1);
	}
	get_exit_code(data, s);
	return (0);
}
