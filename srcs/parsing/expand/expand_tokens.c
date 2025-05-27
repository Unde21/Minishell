#include "minishell.h"
#include "parsing.h"

static void	is_expand(t_args *args)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (args == NULL)
		return ;
	while (args[i].content)
	{
		j = 0;
		args[i].need_expand = false;
		if (args[i].content[j] == ASCII_SNGL_QUOTE)
			args[i].is_quote = false;
		else
			args[i].is_quote = true;
		while (args[i].content[j])
		{
			if ((args[i].content[j] == ASCII_DOLLAR && args[i].is_quote == true)
				|| args[i].content[j] == '*')
				args[i].need_expand = true;
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
		is_expand(current_cmd->args);
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
				if (replace_env_variables(data, &current_cmd->args[i]) == false
					&& current_cmd->args[i].need_expand == true)
					return (false);
			}
			else if (remove_quote(&current_cmd->args[i]) == false)
				return (false);
			++i;
		}
		current_cmd = current_cmd->next;
	}
	return (true);
}
