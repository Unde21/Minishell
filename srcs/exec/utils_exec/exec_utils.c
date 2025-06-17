#include "builtins.h"
#include "exec.h"
#include <unistd.h>

bool	solo_builtin(t_data *data)
{
	if (is_solo_builtin(data->cmd->params))
	{
		if (ft_strcmp(data->cmd->params[0], "echo") == 0)
			ft_echo(data->cmd);
		else if (ft_strcmp(data->cmd->params[0], "pwd") == 0)
			ft_pwd(data);
		else if (ft_strcmp(data->cmd->params[0], "env") == 0)
			ft_env(data, data->cmd);
		else if (ft_strcmp(data->cmd->params[0], "exit") == 0)
			ft_exit(data, data->cmd);
		return (true);
		if (ft_strcmp(data->cmd->params[0], "cd") == 0)
			ft_cd(data, data->cmd);
		else if (ft_strcmp(data->cmd->params[0], "export") == 0)
			ft_export(data);
		else if (ft_strcmp(data->cmd->params[0], "unset") == 0)
			ft_unset(&data->listed_env, data->cmd);
		return (true);
	}
	else
		return (false);
}

bool	child_builtin(t_data *data)
{
	if (is_child_builtin(data->cmd->params))
	{
		if (ft_strcmp(data->cmd->params[0], "echo") == 0)
			ft_echo(data->cmd);
		else if (ft_strcmp(data->cmd->params[0], "pwd") == 0)
			ft_pwd(data);
		else if (ft_strcmp(data->cmd->params[0], "env") == 0)
			ft_env(data, data->cmd);
		else if (ft_strcmp(data->cmd->params[0], "exit") == 0)
			ft_exit(data, data->cmd);
		return (true);
		if (ft_strcmp(data->cmd->params[0], "cd") == 0)
			ft_cd(data, data->cmd);
		else if (ft_strcmp(data->cmd->params[0], "export") == 0)
			ft_export(data);
		else if (ft_strcmp(data->cmd->params[0], "unset") == 0)
			ft_unset(&data->listed_env, data->cmd);
		return (true);
	}
	else
		return (false);
}

bool	is_solo_builtin(char **params)
{
	int		i;
	char	*builtin[7];

	i = 0;
	builtin[0] = "cd";
	builtin[1] = "export";
	builtin[2] = "unset";
	if (params[0])
	{
		while (i < 3)
		{
			if (ft_strcmp(params[0], builtin[i]) == 0)
				return (true);
			else
				i++;
		}
	}
	return (false);
}

bool	is_child_builtin(char **params)
{
	int		i;
	char	*builtin[4];

	i = 0;
	builtin[0] = "echo";
	builtin[1] = "exit";
	builtin[2] = "pwd";
	builtin[3] = "env";
	while (i < 4)
	{
		if (ft_strcmp(params[0], builtin[i]) == 0)
			return (true);
		else
			i++;
	}
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
