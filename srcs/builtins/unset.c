#include "builtins.h"
#include "minishell.h"
#include <stdlib.h>

void	ft_unset(t_env **listed_env, t_cmd *cmd)
{
	t_env	*head;
	t_env	*prev;

	head = *listed_env;
	prev = NULL;
	if (head == NULL || cmd->params[1] == NULL)
		return ;
	while (head)
	{
		if (ft_strcmp(head->key, cmd->params[1]) == 0)
		{
			if (prev == NULL)
				*listed_env = head->next;
			else
				prev->next = head->next;
			free(head->key);
			free(head->value);
			free(head->full_line);
			free(head);
			return ;
		}
		prev = head;
		head = head->next;
	}
}
