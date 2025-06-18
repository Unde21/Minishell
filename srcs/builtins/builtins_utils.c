#include "minishell.h"

void	reset(t_env *listed_env)
{
	t_env	*reset;

	reset = listed_env;
	while (reset)
	{
		reset->printed = 0;
		reset = reset->next;
	}
}
