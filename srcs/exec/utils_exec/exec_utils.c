#include "builtins.h"
#include "exec.h"
#include <unistd.h>

bool	is_builtin(t_data *data)
{
	if (ft_strcmp(data->cmd->params[0], "echo") == 0)
		return (ft_echo(data->cmd));
	else if (ft_strcmp(data->cmd->params[0], "pwd") == 0)
		return (ft_pwd(data));
	else if (ft_strcmp(data->cmd->params[0], "env") == 0)
		return (ft_env(data, data->cmd));
	else if (ft_strcmp(data->cmd->params[0], "exit") == 0)
	{
		ft_exit(data, data->cmd);
		return (true);
	}
	if (ft_strcmp(data->cmd->params[0], "cd") == 0)
		return (ft_cd(data, data->cmd));
	else if (ft_strcmp(data->cmd->params[0], "export") == 0)
		return (ft_export(data));
	else if (ft_strcmp(data->cmd->params[0], "unset") == 0)
		return (ft_unset(&data->listed_env, data->cmd));
	return (false);
}

bool	is_access_ok(char *path, int *return_value)
{
	if (access(path, F_OK) == 0)
	{
		if (access(path, X_OK) == 0)
		{
			*return_value = 0;
			return (true);
		}
		*return_value = 126;
		return (false);
	}
	*return_value = 127;
	return (false);
}
