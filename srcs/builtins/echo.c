#include "builtins.h"
#include "minishell.h"
#include <unistd.h>

bool	ft_echo(t_cmd *cmd)
{
	size_t	i;
	bool	new_line;

	i = 1;
	new_line = true;
	while (cmd->params[i] && ft_strcmp(cmd->params[i], "-n") == 0)
	{
		new_line = false;
		if (cmd->nb_args > 1)
			++i;
	}
	while (cmd->params[i])
	{
		ft_dprintf(STDOUT_FILENO, "%s", cmd->params[i]);
		if (cmd->params[i + 1] != NULL)
			ft_dprintf(STDOUT_FILENO, " ");
		++i;
	}
	if (new_line == true)
		ft_dprintf(STDOUT_FILENO, "\n");
	return (true);
}
