#include "minishell.h"

size_t	get_size_cmd(t_cmd *cmd)
{
	size_t	size;
	t_cmd	*current;

	size = 0;
	current = cmd;
	while (current != NULL)
	{
		++size;
		current = current->next;
	}
	return (size);
}
