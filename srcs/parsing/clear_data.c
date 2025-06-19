#include "minishell.h"
#include <stdlib.h>

void	clear_all_data(t_data *data)
{
	clear_cmd(data);
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

void	clear_cmd(t_data *data)
{
	struct s_cmd	*tmp;

	while (data->cmd != NULL)
	{
		tmp = data->cmd->next;
		if (data->cmd->redir != NULL)
			clear_redir(data->cmd->redir);
		free(data->cmd->args);
		if (data->cmd->params != NULL)
			free_all(data->cmd->params);
		free(data->cmd);
		data->cmd = tmp;
	}
	if (data->ambiguous_file)
	{
		free(data->ambiguous_file);
		data->ambiguous_file = NULL;
	}
	data->cmd = NULL;
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
