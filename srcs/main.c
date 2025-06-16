#include "minishell.h"
#include <unistd.h>
#include <stdlib.h>

int	main(int ac, char **av, char **env)
{
	t_data	data;

	if (!isatty(STDIN_FILENO) || !isatty(STDOUT_FILENO))
		exit(1);
	init_data(&data, ac, av, env);
	get_input(&data);
	return (0);
}
