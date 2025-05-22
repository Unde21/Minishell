#include "builtins.h"
#include "minishell.h"
#include <stdlib.h>

static void	is_number(t_data *data, char *s)
{
	size_t	i;

	i = 0;
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

static int	get_nb_args(t_args *args)
{
	size_t	i;

	i = 0;
	while (args[i].content)
		++i;
	return (i);
}

static void	get_exit_code(t_data *data, char *s)
{
	int	exit_code;
	int	check_error;

	check_error = 0;
	exit_code = ft_atoll(s, &check_error) % 256;
	if (check_error != 0)
	{
		ft_dprintf(2, EXIT_ERROR);
		ft_putstr_fd(s, 2);
		ft_dprintf(2, ERR_NUM_ARG);
		exit(2);
	}
	clear_all_data(data);
	exit(exit_code);
}

int	ft_exit(t_data *data, t_args *args)
{
	char	*s;
	int		nb_args;

	nb_args = get_nb_args(args);
	if (nb_args == 1)
		s = "0";
	else
		s = args[1].content;
	ft_printf("s : %s\n", s);
	is_number(data, s);
	ft_printf("nb_args : %d\n", nb_args);
	if (nb_args > 2)
	{
		ft_dprintf(2, EXIT_TOO_MANY);
		data->return_value = 127;
		return (-1);
	}
	get_exit_code(data, s);
	return (0);
}
