#include "minishell.h"
#include "parsing.h"

static void	is_expand(t_cmd *cmd)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (cmd->params == NULL)
		return ;
	while (cmd->params[i])
	{
		j = 0;
		cmd->args[i].need_expand = false;
		if (cmd->params[i][j] == ASCII_SNGL_QUOTE)
			cmd->args[i].is_quote = false;
		else
			cmd->args[i].is_quote = true;
		while (cmd->params[i][j])
		{
			if ((cmd->params[i][j] == ASCII_DOLLAR
				&& cmd->args[i].is_quote == true) || cmd->params[i][j] == '*')
				cmd->args[i].need_expand = true;
			if (cmd->params[i][j] == '*')
				cmd->args[i].is_wildcards = true;
			++j;
		}
		++i;
	}
}

void	expand_tokens(t_cmd *cmd)
{
	t_cmd	*current_cmd;

	current_cmd = cmd;
	while (current_cmd != NULL)
	{
		is_expand(current_cmd);
		current_cmd = current_cmd->next;
	}
}

bool	handle_expansion(t_data *data, t_cmd *cmd)
{
	t_cmd	*current_cmd;
	size_t	i;

	i = 0;
	current_cmd = cmd;
	while (current_cmd != NULL)
	{
		i = 0;
		while (i < current_cmd->nb_args)
		{
			if (current_cmd->args[i].need_expand == true)
			{
				if (replace_env_variables(data,
						&current_cmd->params[i], i) == false
					&& current_cmd->args[i].need_expand == true)
					return (false);
			}
			else if (remove_quote(data, &current_cmd->params[i]) == false)
					return (false);
			++i;
		}
		current_cmd = current_cmd->next;
	}
	return (true);
}
