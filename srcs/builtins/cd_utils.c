#include "builtins.h"
#include "minishell.h"

void	display_error(t_data *data, char *params)
{
	ft_dprintf(2, CD_ERR);
	ft_dprintf(2, "%s: ", params);
	ft_dprintf(2, CD_NO_DIR);
	data->return_value = 1;
}
