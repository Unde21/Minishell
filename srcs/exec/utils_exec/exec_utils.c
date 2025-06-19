#include "builtins.h"
#include "exec.h"
#include "parsing.h"
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

bool	is_builtin(t_data *data)
{
	if (data->cmd->params[0] == NULL)
		return (false);
	if (ft_strcmp(data->cmd->params[0], "echo") == 0)
		return (true);
	else if (ft_strcmp(data->cmd->params[0], "pwd") == 0)
		return (true);
	else if (ft_strcmp(data->cmd->params[0], "env") == 0)
		return (true);
	else if (ft_strcmp(data->cmd->params[0], "exit") == 0)
		return (true);
	else if (ft_strcmp(data->cmd->params[0], "cd") == 0)
		return (true);
	else if (ft_strcmp(data->cmd->params[0], "export") == 0)
		return (true);
	else if (ft_strcmp(data->cmd->params[0], "unset") == 0)
		return (true);
	return (false);
}

void	execute_builtins(t_data *data, t_cmd *head)
{
	if (data->cmd->params[0] == NULL)
		return ;
	if (ft_strcmp(data->cmd->params[0], "echo") == 0)
		ft_echo(data->cmd);
	else if (ft_strcmp(data->cmd->params[0], "pwd") == 0)
		ft_pwd(data);
	else if (ft_strcmp(data->cmd->params[0], "env") == 0)
		ft_env(data, data->cmd);
	else if (ft_strcmp(data->cmd->params[0], "exit") == 0)
		ft_exit(data, data->cmd, head);
	else if (ft_strcmp(data->cmd->params[0], "cd") == 0)
		ft_cd(data, data->cmd);
	else if (ft_strcmp(data->cmd->params[0], "export") == 0)
		ft_export(data);
	else if (ft_strcmp(data->cmd->params[0], "unset") == 0)
		ft_unset(data, data->cmd);
}

bool	print_access_error(char *params, t_data *data)
{
	if (data->return_value == 1)
		print_err_null(ERR_MALLOC);
	else if (data->return_value == 127)
		ft_dprintf(STDERR_FILENO, "%s%s", params, CMD_NOT_FOUND);
	else if (data->return_value == 126)
	{
		data->return_value = 126;
		ft_dprintf(STDERR_FILENO, "%s%s", params, NO_FILE);
	}
	else
		data->return_value = 126;
	return (false);
}

static bool	is_directory(char *path, t_data *data)
{
	struct stat	s;

	if (stat(path, &s) != 0)
	{
		data->return_value = 127;
		return (false);
	}
	if (S_ISDIR(s.st_mode))
	{
		ft_dprintf(2, "%s %s", path, ERR_IS_DIR);
		data->return_value = -42;
		return (false);
	}
	return (true);
}

bool	is_access_ok(char *path, char **params, t_data *data)
{
	if (params[0][0] == '\0' || params == NULL)
	{
		data->return_value = 127;
		return (false);
	}
	if (is_directory(path, data) == false)
		return (false);
	if (access(path, F_OK) == 0)
	{
		if (access(path, X_OK) == 0)
		{
			data->return_value = 0;
			return (true);
		}
		data->return_value = 126;
		return (false);
	}
	data->return_value = 127;
	return (false);
}
