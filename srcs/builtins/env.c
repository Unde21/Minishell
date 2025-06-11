#include "builtins.h"
#include "minishell.h"
#include "parsing.h"

static bool	print_error_env(t_cmd *cmd)
{
	size_t	i;

	i = 0;
	if (cmd->nb_args > 1)
	{
		if (cmd->args->is_quote == true)
		{
			ft_dprintf(2, ERR_ENV);
			while (cmd->params[++i])
			{
				ft_dprintf(2, "%s", cmd->params[i]);
				if (cmd->params[i + 1] != NULL)
					ft_dprintf(2, " ");
			}
			ft_dprintf(2, ENV_TOO_MANY);
		}
		else
		{
			ft_dprintf(2, ERR_ENV);
			ft_dprintf(2, "%s’: ", cmd->params[i]);
			ft_dprintf(2, ENV_NO_FILE);
		}
		return (false);
	}
	return (true);
}

void	ft_env(t_data *data, t_cmd *cmd)
{
	t_env	*current;

	current = data->listed_env;
	if (print_error_env(cmd) == false)
	{
		data->return_value = 127;
		return ;
	}
	while (current != NULL)
	{
		ft_printf("%s\n", current->full_line);
		current = current->next;
	}
}
