#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

# define EXIT_ERROR "bash: exit: "
# define EXIT_TOO_MANY "bash: exit: too many arguments\n"
# define ERR_NUM_ARG ": numeric argument required\n"

// ft_exit.c
int	ft_exit(t_data *data, t_args *args);

#endif
