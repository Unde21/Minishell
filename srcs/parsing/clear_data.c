#include "minishell.h"
#include <stdlib.h>

static void	clear_args(t_cmd *cmd)
{
	size_t	i;

	i = 0;
	while (i < cmd->nb_args)
	{
		if (cmd->args != NULL)
		{
			free(cmd->args[i].content);
			cmd->args[i].content = NULL;
		}
		++i;
	}
	free(cmd->args);
	cmd->args = NULL;
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
		redir = NULL;
		redir = tmp;
	}
	redir = NULL;
}

void	clear_cmd(t_cmd *cmd)
{
	t_cmd	*tmp;

	while (cmd != NULL)
	{
		tmp = cmd->next;
		if (cmd->redir != NULL)
		{
			clear_redir(cmd->redir);
		}
		clear_args(cmd);
		free(cmd);
		cmd = NULL;
		cmd = tmp;
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
	if (str == NULL)
		return ;
	while (str[i])
	{
		free(str[i]);
		++i;
	}
	free(str);
}
