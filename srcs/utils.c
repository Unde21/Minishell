#include "minishell.h"
#include "parsing.h"
#include <unistd.h>

bool	print_err(char *str_error)
{
	ft_dprintf(STDERR_FILENO, "%s", str_error);
	return (false);
}

void	reset_g_return_value(t_data *data)
{
	if (g_return_value != 0)
	{
		data->return_value = g_return_value;
		g_return_value = 0;
	}
}

void	print_access_error(char *params, t_data *data)
{
	if (data->return_value == 1)
	{
		print_err(ERR_MALLOC);
		return ;
	}
<<<<<<< HEAD
	ft_dprintf(STDERR_FILENO, "bash: %s: ", params);
	ft_dprintf(STDERR_FILENO, "command not found\n");
=======
	// data->return_value = 127;
	ft_dprintf(2, "bash: %s: ", params);
	ft_dprintf(2, "command not found\n");
>>>>>>> origin/norm_leak
}

void	print_ambiguous(char *s)
{
	ft_dprintf(STDERR_FILENO, PRINT_BASH);
	ft_dprintf(STDERR_FILENO, " %s: ", s);
	ft_dprintf(STDERR_FILENO, ERR_AMBIGUOUS);
}
