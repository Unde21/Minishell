#include "builtins.h"
#include "exec.h"
#include "minishell.h"
#include <stdlib.h>

bool	ft_unset(t_env **listed_env, t_cmd *cmd)
{
	t_env	*head;
	t_env	*prev;
	char	*key;
	int		i;

	i = 0;
	while (cmd->params[++i])
	{
		prev = NULL;
		head = *listed_env;
		key = get_key(cmd->params[i]); // Leak si MALLOC == NULL
		while (head)
		{
			if (ft_strcmp(head->key, key) == 0)
			{
				if (prev)
					prev->next = head->next;
				else
					*listed_env = head->next;
			}
			prev = head;
			head = head->next;
		}
	}
	return (true);
}
