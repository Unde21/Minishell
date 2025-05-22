#include "minishell.h"
#include "parsing.h"

bool	print_err(char *str_error)
{
	ft_dprintf(2, "%s", str_error);
	return (false);
}
