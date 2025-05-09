

#include "minishell.h"

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
			if (args[i].content[j] == ASCII_DOLLAR && args[i].is_quote == true)
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
