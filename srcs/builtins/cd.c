#include "builtins.h"
#include "minishell.h"
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

static void	display_error(t_data *data, char *params)
{
	ft_dprintf(2, CD_ERR);
	ft_dprintf(2, "%s: ", params);
	ft_dprintf(2, CD_NO_DIR);
	data->return_value = 1;
}

void	ft_cd(t_data *data, t_cmd *cmd)
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
			return ;
		}
		if (chdir(home_path) == -1)
			display_error(data, cmd->params[1]);
	}
	else if (chdir(cmd->params[1]) == -1)
		display_error(data, cmd->params[1]);
}
