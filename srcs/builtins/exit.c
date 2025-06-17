#include "builtins.h"
#include "minishell.h"
#include <stdlib.h>

static void	is_number(t_data *data, char *s)
{
	size_t	i;

	i = 0;
	if (s == NULL)
		return ;
	while (s[i])
	{
		if (ft_isdigit(s[i]) == 0)
		{
			ft_dprintf(2, EXIT_ERROR);
			ft_putstr_fd(s, 2);
			ft_dprintf(2, ERR_NUM_ARG);
			clear_all_data(data);
			exit(2);
		}
		++i;
	}
}

static void	get_exit_code(t_data *data, char *s)
{
	int	exit_code;
	int	check_error;

	check_error = 0;
	if (s == NULL)
		exit_code = data->return_value;
	else
		exit_code = ft_atoll(s, &check_error) % 256;
	if (check_error != 0)
	{
		ft_dprintf(2, EXIT_ERROR);
		ft_dprintf(2, "%s", s);
		ft_dprintf(2, ERR_NUM_ARG);
		exit(2);
	}
	clear_all_data(data);
	exit(exit_code);
}

int	ft_exit(t_data *data, t_cmd *cmd)
{
	char	*s;
	int		exit_code;

	exit_code = 0;
	if (cmd->nb_args == 1)
	{
		exit_code = data->return_value;
		clear_all_data(data);
		exit(exit_code);
	}
	else
		s = cmd->params[1];
	is_number(data, s);
	if (cmd->nb_args > 2)
	{
		ft_dprintf(2, EXIT_TOO_MANY);
		data->return_value = 1;
		return (-1);
	}
	get_exit_code(data, s);
	return (0);
}
