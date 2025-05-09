#include "minishell.h"
#include "parsing.h"
#include <stdlib.h>
#include <unistd.h>

void	get_input(t_data *data)
{
	char	*str;
	char	*path;

	// TODO Voir ce qu on met !
	path = getcwd(NULL, 0);
	str = ft_strjoin(path, "$ ");
	free(path);
	data->line_read = readline(str);
	if (data->line_read != NULL)
		add_history(data->line_read);
	while (data->line_read != NULL)
	{
		parsing(data); // BUG segfault if input == NULL
		free(data->line_read);
		data->line_read = readline(str);
		if (data->line_read != NULL)
			add_history(data->line_read);
	}
	rl_clear_history();
	free(data->line_read);
	free(str);
}
