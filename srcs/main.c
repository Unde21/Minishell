
#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	t_data	data;

	init_data(&data, ac, av, env);
	get_input(&data);
	return (0);
}
