#include "builtins.h"
#include "minishell.h"
#include "parsing.h"
#include <stdlib.h>
#include <unistd.h>

static char	*get_home_path(t_env *env)
{
	t_env	*current;

	current = env;
	while (current != NULL)
	{
		if (ft_strcmp(current->key, CD_HOME) == 0)
			return (current->value);
		current = current->next;
	}
	return (NULL);
}

static bool	update_pwd(t_data *data, t_env *current)
{
	current->value = getcwd(NULL, 0);
	if (current->value == NULL)
	{
		ft_dprintf(2, ERR_PWD);
		data->return_value = 1;
		return (false);
	}
	current->full_line = ft_strdup(current->key);
	current->full_line = ft_strjoin_and_free(current->full_line, "=");
	current->full_line = ft_strjoin_and_free(current->full_line,
			current->value);
	if (current->full_line == NULL)
	{
		ft_dprintf(2, ERR_PWD);
		data->return_value = 1;
		return (false);
	}
	return (true);
}

static bool	update_oldpwd(t_data *data, t_env *current, t_env *old)
{
	current->value = ft_strdup(old->value);
	if (current->value == NULL)
	{
		ft_dprintf(2, ERR_PWD);
		data->return_value = 1;
		return (false);
	}
	current->full_line = ft_strdup(old->full_line);
	if (current->full_line == NULL)
	{
		ft_dprintf(2, ERR_PWD);
		data->return_value = 1;
		return (false);
	}
	return (true);
}

static void	update_listed_env(t_data *data, t_env *env)
{
	t_env	*pwd_env;
	t_env	*oldpwd_env;
	t_env	*current;

	pwd_env = NULL;
	oldpwd_env = NULL;
	current = env;
	while (current != NULL)
	{
		if (ft_strcmp(current->key, PWD) == 0)
			pwd_env = current;
		else if (ft_strcmp(current->key, OLDPWD) == 0)
			oldpwd_env = current;
		current = current->next;
	}
	if (pwd_env == NULL || oldpwd_env == NULL)
	{
		data->return_value = 1;
		return ;
	}
	update_oldpwd(data, oldpwd_env, pwd_env);
	update_pwd(data, pwd_env);
}

bool	ft_cd(t_data *data, t_cmd *cmd)
{
	char	*home_path;

	home_path = NULL;
	if (cmd->params[1] == NULL)
	{
		home_path = get_home_path(data->listed_env);
		if (home_path == NULL)
		{
			ft_dprintf(2, CD_ERR);
			ft_dprintf(2, CD_NO_DIR);
			data->return_value = 1;
			return (true);
		}
		if (chdir(home_path) == -1)
		{
			display_error(data, cmd->params[1]);
			return (true);
		}
	}
	else if (chdir(cmd->params[1]) == -1)
	{
		display_error(data, cmd->params[1]);
		return (true);
	}
	update_listed_env(data, data->listed_env);
	return (true);
}
