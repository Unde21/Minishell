#include "builtins.h"
#include "minishell.h"
#include <unistd.h>
#include <stdlib.h>

void	ft_pwd(t_data *data)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (path == NULL)
	{
		ft_dprintf(2, ERR_PWD);
		data->return_value = 1;
		return ;
	}
	ft_printf("%s\n", path);
	free(path);
}
