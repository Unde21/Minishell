#include "builtins.h"
#include "exec.h"

static void	clear_listed_env(t_env **listed_env)
{
	t_env	*head;

	head = *listed_env;
	if (head == NULL)
		return ;
	while (head)
	{
		free(head->key);
		free(head->value);
		free(head->full_line);
		free(head);
		head = head->next;
	}
}

void	clear_exec(t_data *data)
{
	clear_listed_env(&data->listed_env);
}