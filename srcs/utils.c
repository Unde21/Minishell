#include "minishell.h"
#include "parsing.h"

bool	print_err(char *str_error)
{
	ft_dprintf(2, "%s", str_error);
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

void	print_access_error(char *params)
{
	ft_dprintf(2, "bash: %s: ", params);
	ft_dprintf(2, "command not found\n");
}

void	print_ambiguous(char *s)
{
	ft_dprintf(2, PRINT_BASH);
	ft_dprintf(2, " %s: ", s);
	ft_dprintf(2, ERR_AMBIGUOUS);
}
