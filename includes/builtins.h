#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

# define EXIT_ERROR "bash: exit: "
# define EXIT_TOO_MANY "bash: exit: too many arguments\n"
# define ERR_NUM_ARG ": numeric argument required\n"
# define ENV_TOO_MANY "‘: No such file or directory\n\
env: use -[v]S to pass options in shebang lines\n"
# define ERR_ENV "env: ‘"
# define ENV_NO_FILE "No such file or directory\n"

// ft_exit.c
int		ft_exit(t_data *data, t_args *args);

// ft_echo.c
void	ft_echo(t_cmd *cmd);

// ft_env
void	ft_env(t_data *data, t_cmd *cmd);

#endif
