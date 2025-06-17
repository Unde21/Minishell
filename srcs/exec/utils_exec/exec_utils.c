#include "builtins.h"
#include "exec.h"
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

void	execute_builtins(t_data *data)
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
		ft_exit(data, data->cmd);
	else if (ft_strcmp(data->cmd->params[0], "cd") == 0)
		ft_cd(data, data->cmd);
	else if (ft_strcmp(data->cmd->params[0], "export") == 0)
		ft_export(data);
	else if (ft_strcmp(data->cmd->params[0], "unset") == 0)
		ft_unset(data, &data->listed_env, data->cmd);
}

bool	is_access_ok(char *path, int *return_value, char **params)
{
	if (params[0][0] == '\0' || params == NULL)
	{
		*return_value = 127;
		return (false);
	}
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
