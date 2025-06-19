#include "minishell.h"
#include <stdlib.h>

void	clear_all_data(t_data *data)
{
	clear_cmd(data, data->cmd);
	clear_token(data->token_lst->head);
	free(data->token_lst);
	free(data->line_read);
}

static void	clear_redir(t_redir *redir)
{
	t_redir	*tmp;

	while (redir != NULL)
	{
		tmp = redir->next;
		if (redir->file != NULL)
		{
			free(redir->file);
			redir->file = NULL;
		}
		free(redir);
		redir = tmp;
	}
	redir = NULL;
}

void	clear_cmd(t_data *data, t_cmd *cmd)
{
	struct s_cmd	*tmp;

	while (cmd != NULL)
	{
		tmp = cmd->next;
		if (cmd->redir != NULL)
			clear_redir(cmd->redir);
		free(cmd->args);
		if (cmd->params != NULL)
			free_all(cmd->params);
		free(cmd);
		cmd = tmp;
	}
	if (data->ambiguous_file)
	{
		free(data->ambiguous_file);
		data->ambiguous_file = NULL;
	}
	cmd = NULL;
}

void	clear_token(t_token *lst)
{
	t_token	*tmp;

	while (lst != NULL)
	{
		tmp = lst->next;
		if (lst->content != NULL)
		{
			free(lst->content);
			lst->content = NULL;
		}
		free(lst);
		lst = NULL;
		lst = tmp;
	}
	lst = NULL;
}

void	free_all(char **str)
{
	size_t	i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}
