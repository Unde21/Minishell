#include "builtins.h"
#include <unistd.h>

bool	is_new_line(size_t *i, t_cmd *cmd)
{
	bool	new_line;
	size_t	j;

	new_line = true;
	while (cmd->params[*i] && cmd->params[*i][0] == '-')
	{
		j = 1;
		while (cmd->params[*i][j] && cmd->params[*i][j] == 'n')
			++j;
		if (j > 1 && cmd->params[*i][j] == '\0')
		{
			new_line = false;
			(*i)++;
		}
		else
			break ;
	}
	return (new_line);
}

bool	ft_echo(t_cmd *cmd)
{
	size_t	i;
	bool	new_line;

	i = 1;
	new_line = is_new_line(&i, cmd);
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
