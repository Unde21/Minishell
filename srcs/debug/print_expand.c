#include "debug.h"

static void	print_cmd_args_expanded(t_cmd *cmd)
{
	size_t	i;

	i = 0;
	if (cmd->args == NULL)
		return ;
	while (cmd->args[i].content)
	{
		if (i == 0)
			ft_printf("\033[35m[%s]\033[0m", cmd->args[i].content);
		else
			ft_printf("\n\033[35m[%s]\033[0m", cmd->args[i].content);
		++i;
	}
}

static void	print_special_operator_expand(t_redir *current_redir)
{
	while (current_redir != NULL)
	{
		if (current_redir->type == 4)
			ft_printf("%s", EXPAND_REDIR_IN);
		else if (current_redir->type == 5)
			ft_printf("%s", EXPAND_REDIR_OUT);
		else if (current_redir->type == 6)
			ft_printf("%s", EXPAND_HERE_DOC);
		else if (current_redir->type == 7)
			ft_printf("%s", EXPAND_APPEND);
		ft_printf(" && \033[35mFILE: %s\033[0m", current_redir->file);
		current_redir = current_redir->next;
	}
}

void	print_lst_cmd_expand(t_cmd *cmd)
{
	size_t	i;
	t_redir	*current_redir;

	if (cmd == NULL)
		return ;
	ft_printf("%s", PRINT_EXPAND);
	while (cmd != NULL)
	{
		i = 0;
		ft_printf("%s", START_SEP_LINE_EXPAND);
		print_cmd_args_expanded(cmd);
		current_redir = cmd->redir;
		print_special_operator_expand(current_redir);
		ft_printf("%s", END_SEP_LINE_EXPAND);
		ft_printf("%s", NEXT_NODE);
		cmd = cmd->next;
	}
	ft_printf("%s", PRINT_NULL_EXPAND);
	ft_printf("%s", END_SEP_LINE_EXPAND);
}
