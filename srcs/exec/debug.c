// #include "exec.h"

// void	print_listed_env(t_data *data)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	j = -1;
// 	while (data->listed_env->next != NULL)
// 	{
// 		printf("# => %d\n", i++);
// 		printf("key => %s\n", data->listed_env->key);
// 		printf("value => %s\n", data->listed_env->value);
// 		printf("full_line => %s\n\n", data->listed_env->full_line);
// 		data->listed_env = data->listed_env->next;
// 	}
// }
// void	print_env(t_data *data)
// {
// 	int	i;

// 	i = -1;
// 	while (data->env[++i])
// 		printf("# = %d\nenv = %s\n\n", i, data->env[i]);
// }

// void	print_lst(t_token *token, int t)
// {
// 	if (token == NULL)
// 		return ;
// 	if (t == 1)
// 	{
// 		ft_printf("\n\033[37;45mPRINT TOKENISER:\033[0m\n\n");
// 		while (token != NULL)
// 		{
// 			ft_printf("\033[35m-------------------------------------------------------------------------\033[0m\n{");
// 			if (token->type == 0)
// 				ft_printf("\033[33m%s}		type: WORD\033[0m", token->content);
// 			else if (token->type == 1)
// 				ft_printf("\033[33m%s}		type: SNGL_QUOTE\033[0m",
// 							token->content);
// 			else if (token->type == 2)
// 				ft_printf("\033[33m%s}		type: DBLE_QUOTE\033[0m",
// 							token->content);
// 			else if (token->type == 3)
// 				ft_printf("\033[33m%s}		type: PIPE\033[0m", token->content);
// 			else if (token->type == 4)
// 				ft_printf("\033[33m%s}		type: REDIR_IN\033[0m",
// 							token->content);
// 			else if (token->type == 5)
// 				ft_printf("\033[33m%s}		type: REDIR_OUT\033[0m",
// 							token->content);
// 			else if (token->type == 6)
// 				ft_printf("\033[33m%s}		type: HERE_DOC\033[0m",
// 							token->content);
// 			else if (token->type == 7)
// 				ft_printf("\033[33m%s}		type: APPEND\033[0m",
// 							token->content);
// 			ft_printf("\n\033[35m-------------------------------------------------------------------------\033[0m\n");
// 			ft_printf("       				|\n      				v\n");
// 			token = token->next;
// 		}
// 		ft_printf("\033[35m-------------------------------------------------------------------------\n\033[33m{NULL}\033[0m");
// 		ft_printf("\n\033[35m-------------------------------------------------------------------------\033[0m\n");
// 	}
// 	else if (t == 2)
// 	{
// 		while (token != NULL)
// 		{
// 			printf("%s\n", token->content);
// 			token = token->next;
// 		}
// 	}
// }
// void	print_lst_cmd(t_cmd *cmd)
// {
// 	size_t	i;
// 	t_redir	*current_redir;

// 	if (cmd == NULL)
// 		return ;
// 	printf("\n\n\n\033[31;44mPRINT PARSER:\033[0m\n\n");
// 	while (cmd != NULL)
// 	{
// 		i = 0;
// 		ft_printf("\033[34m-------------------------------------------------------------------------\033[0m\n");
// 		while (cmd->args[i].content)
// 		{
// 			if (i == 0)
// 				ft_printf("\033[32m%s\033[0m", cmd->args[i].content);
// 			else
// 				ft_printf("\n\033[32m%s\033[0m", cmd->args[i].content);
// 			if (cmd->args[i].need_expand == true)
// 				ft_printf("	\033[32m--> need_expend: Yes\033[0m");
// 			else
// 				ft_printf("	\033[32m--> need_expend: No\033[0m");
// 			++i;
// 		}
// 		current_redir = cmd->redir;
// 		while (current_redir != NULL)
// 		{
// 			if (current_redir->type == 4)
// 				ft_printf("\033[32m		REDIR: REDIR_IN	\033[0m");
// 			else if (current_redir->type == 5)
// 				ft_printf("\033[32m		REDIR: REDIR_OUT\033[0m");
// 			else if (current_redir->type == 6)
// 				ft_printf("\033[32m		REDIR: HERE_DOC	\033[0m");
// 			else if (current_redir->type == 7)
// 				ft_printf("\033[32m		REDIR: APPEND\033[0m");
// 			ft_printf("		\033[32mFILE: %s\n\033[0m", current_redir->file);
// 			current_redir = current_redir->next;
// 		}
// 		ft_printf("\n\033[34m-------------------------------------------------------------------------\033[0m\n");
// 		ft_printf("       				|\n      				v\n");
// 		cmd = cmd->next;
// 	}
// 	ft_printf("\033[34m-------------------------------------------------------------------------\033[0m\n\033[32mNULL\033[0m");
// 	ft_printf("\n\033[34m-------------------------------------------------------------------------\033[0m\n");
// }

// void	print_lst_cmd_expand(t_cmd *cmd)
// {
// 	size_t i;
// 	t_redir *current_redir;

// 	if (cmd == NULL)
// 		return ;
// 	printf("\n\n\n\033[35;43mPRINT PARSER WITH EXPAND:\033[0m\n\n");
// 	while (cmd != NULL)
// 	{
// 		i = 0;
// 		ft_printf("\033[33m-------------------------------------------------------------------------\033[0m\n");
// 		while (cmd->args[i].content)
// 		{
// 			if (cmd->args[i].content == NULL)
// 				break ;
// 			if (i == 0)
// 				ft_printf("\033[35m%s\033[0m", cmd->args[i].content);
// 			else
// 				ft_printf("\n\033[35m%s\033[0m", cmd->args[i].content);
// 			++i;
// 		}
// 		current_redir = cmd->redir;
// 		while (current_redir != NULL)
// 		{
// 			if (current_redir->type == 4)
// 				ft_printf("\033[35m		REDIR: REDIR_IN	\033[0m");
// 			else if (current_redir->type == 5)
// 				ft_printf("\033[35m		REDIR: REDIR_OUT\033[0m");
// 			else if (current_redir->type == 6)
// 				ft_printf("\033[35m		REDIR: HERE_DOC	\033[0m");
// 			else if (current_redir->type == 7)
// 				ft_printf("\033[35m		REDIR: APPEND\033[0m");
// 			ft_printf("		\033[35mFILE: %s\n\033[0m", current_redir->file);
// 			current_redir = current_redir->next;
// 		}
// 		ft_printf("\n\033[33m-------------------------------------------------------------------------\033[0m\n");
// 		ft_printf("       				|\n      				v\n");
// 		cmd = cmd->next;
// 	}
// 	ft_printf("\033[33m-------------------------------------------------------------------------\033[0m\n\033[35mNULL\033[0m");
// 	ft_printf("\n\033[33m-------------------------------------------------------------------------\033[0m\n");
// }