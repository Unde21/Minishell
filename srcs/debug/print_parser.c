#include "debug.h"

static void	print_special_operator_parser(t_redir *current_redir)
{
	while (current_redir != NULL)
	{
		if (current_redir->type == 4)
			ft_printf("%s", PARSER_REDIR_IN);
		else if (current_redir->type == 5)
			ft_printf("%s", PARSER_REDIR_OUT);
		else if (current_redir->type == 6)
			ft_printf("%s", PARSER_HERE_DOC);
		else if (current_redir->type == 7)
			ft_printf("%s", PARSER_APPEND);
		if (current_redir->type != 6)
			ft_printf(" && \033[32mFILE = %s\033[0m", current_redir->file);
		else
			ft_printf(" && \033[32mLIMITER = %s\033[0m", current_redir->file);
		current_redir = current_redir->next;
	}
}

static void	print_cmd_args(t_cmd *cmd)
{
	size_t	i;

	i = 0;
	if (cmd->params == NULL)
		return ;
	while (cmd->params[i])
	{
		if (i == 0)
			ft_printf("\033[32m[%s]\033[0m", cmd->params[i]);
		else
			ft_printf("\n\033[32m[%s]\033[0m", cmd->params[i]);
		if (cmd->args[i].need_expand == true)
			ft_printf("%s", EXPAND_YES);
		else
			ft_printf("%s", EXPAND_NO);
		++i;
	}
}

void	print_lst_cmd(t_cmd *cmd)
{
	t_redir	*current_redir;

	if (cmd == NULL)
		return ;
	ft_printf("%s", PRINT_PARSER);
	while (cmd != NULL)
	{
		ft_printf("%s", START_SEP_LINE_PARSER);
		print_cmd_args(cmd);
		current_redir = cmd->redir;
		print_special_operator_parser(current_redir);
		ft_printf("%s%s", END_SEP_LINE_PARSER, NEXT_NODE);
		cmd = cmd->next;
	}
	ft_printf("%s%s", PRINT_NULL_PARSER, END_SEP_LINE_PARSER);
}
