#include "builtins.h"
#include "minishell.h"
#include <unistd.h>

void	ft_pwd(t_data *data, t_cmd *cmd)
{
	(void)data;
	(void)cmd;
	ft_printf("%s\n", getcwd(NULL, 0));
}
