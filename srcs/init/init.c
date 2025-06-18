#include "parsing.h"
#include <stdlib.h>
#include <unistd.h>

bool	init_data(t_data *data, int ac, char **av, char **env)
{
	ft_memset(data, 0, sizeof(t_data));
	data->ac = ac;
	data->av = av;
	data->env = env;
	init_listed_env(data);
	if (data->return_value != 0)
		return (false);
	return (true);
}

bool	init_cmd_args(t_cmd *cmd)
{
	size_t	i;

	i = 0;
	cmd->params = malloc(sizeof(char *) * (cmd->nb_args + 1));
	if (cmd->params == NULL)
		return (print_err_false(ERR_MALLOC));
	cmd->args = malloc(sizeof(t_args) * (cmd->nb_args + 1));
	if (cmd->args == NULL)
		return (print_err_false(ERR_MALLOC));
	while (i <= cmd->nb_args)
	{
		cmd->args[i].is_wildcards = false;
		cmd->args[i].need_expand = false;
		cmd->args[i].content = NULL;
		cmd->args[i].is_quote = false;
		++i;
	}
	if (cmd->nb_args == 0)
		cmd->args[0].content = NULL;
	return (true);
}

static bool	init_cmd(t_data *data)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (cmd == NULL)
		return (print_err_false(ERR_MALLOC));
	ft_memset(cmd, 0, sizeof(t_cmd));
	cmd->fd_out = 1;
	cmd->fd_in = 0;
	cmd->pipe_fd[0] = -1;
	cmd->pipe_fd[1] = -1;
	data->cmd = cmd;
	return (true);
}

static bool	init_token(t_data *data)
{
	t_token_lst	*tokens;
	t_token		*current;

	tokens = malloc(sizeof(t_token_lst));
	if (tokens == NULL)
		return (print_err_false(ERR_MALLOC));
	tokens->head = NULL;
	tokens->tail = NULL;
	current = NULL;
	data->token = current;
	data->token_lst = tokens;
	return (true);
}

bool	init_lst(t_data *data)
{
	if (init_token(data) == false)
		return (false);
	else if (init_cmd(data) == false)
	{
		clear_token(data->token_lst->head);
		free(data->token_lst);
		data->token_lst = NULL;
		return (false);
	}
	data->had_space_before = true;
	return (true);
}
