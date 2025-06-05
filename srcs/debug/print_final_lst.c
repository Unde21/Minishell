#include "debug.h"

static void	print_cmd_params(t_cmd *cmd)
{
	size_t	i;

	i = 0;
	if (cmd->params == NULL)
		return ;
	while (cmd->params[i])
	{
		if (i == 0)
			ft_printf("\033[93m[%s]\033[0m", cmd->params[i]);
		else
			ft_printf("\n\033[96m[%s]\033[0m", cmd->params[i]);
		++i;
	}
}

static void	print_special_operator(t_redir *current_redir)
{
	while (current_redir != NULL)
	{
		if (current_redir->type == 4)
			ft_printf("%s", FINAL_REDIR_IN);
		else if (current_redir->type == 5)
			ft_printf("%s", FINAL_REDIR_OUT);
		else if (current_redir->type == 6)
			ft_printf("%s", FINAL_HERE_DOC);
		else if (current_redir->type == 7)
			ft_printf("%s", FINAL_APPEND);
		ft_printf(" && \033[96mFILE: %s\033[0m", current_redir->file);
		current_redir = current_redir->next;
	}
}

void	print_final_lst(t_cmd *cmd)
{
	size_t	i;
	t_redir	*current_redir;

	if (cmd == NULL)
		return ;
	ft_printf("%s", PRINT_FINAL_LST);
	while (cmd != NULL)
	{
		i = 0;
		ft_printf("%s", START_SEP_LINE_FINAL);
		print_cmd_params(cmd);
		current_redir = cmd->redir;
		print_special_operator(current_redir);
		ft_printf("%s", END_SEP_LINE_FINAL);
		ft_printf("%s", NEXT_NODE);
		cmd = cmd->next;
	}
	ft_printf("%s", PRINT_NULL_FINAL);
	ft_printf("%s", END_SEP_LINE_FINAL);
}
