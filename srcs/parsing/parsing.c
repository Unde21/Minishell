#include "builtins.h"
#include "debug.h"
#include "minishell.h"
#include <stdlib.h>

static bool	tokenizer(t_data *data)
{
	if (handle_token(data, data->line_read, data->token_lst,
			data->token) == false)
		return (false);
	if (DEBUG_VALUE == 1 || DEBUG_VALUE == 5)
		print_lst(data->token_lst->head);
	return (true);
}

#include <fcntl.h>
#include <unistd.h>

bool	parsing(t_data *data)
{
	int	prev_return_value;

	prev_return_value = data->return_value;
	data->return_value = 0;
	if (tokenizer(data) == false)
		return (false);
	if (parser(data, &data->cmd) == false)
		return (false);
	expand_tokens(data->cmd);
	if (DEBUG_VALUE == 2 || DEBUG_VALUE == 5)
		print_lst_cmd(data->cmd);
	if (data->return_value == 0)
		data->return_value = prev_return_value;
	if (handle_expansion(data, data->cmd) == false)
		return (false);
	if (DEBUG_VALUE == 3 || DEBUG_VALUE == 5)
		print_lst_cmd_expand(data->cmd);
	if (ft_strcmp(data->cmd->params[0], "exit") == 0)
		ft_exit(data, data->cmd); // exit
	else if (ft_strcmp(data->cmd->params[0], "echo") == 0)
		ft_echo(data->cmd);
	else if (ft_strcmp(data->cmd->params[0], "pwd") == 0)
		ft_pwd(data, data->cmd);
	// else if (ft_strcmp(data->cmd->params[0], "cd") == 0)
	// 	ft_cd(data, data->cmd);
	// else
	// 	execve("/usr/bin/ls", data->cmd->params, data->env);
	return (true);
}
