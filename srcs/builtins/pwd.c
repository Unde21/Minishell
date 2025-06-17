#include "builtins.h"
#include "minishell.h"
#include <stdlib.h>
#include <unistd.h>

bool	ft_pwd(t_data *data)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (path == NULL)
	{
		ft_dprintf(2, ERR_PWD);
		data->return_value = 1;
		return (true);
	}
	ft_dprintf(STDOUT_FILENO, "%s\n", path);
	free(path);
	return (true);
}
