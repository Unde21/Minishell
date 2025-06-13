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
