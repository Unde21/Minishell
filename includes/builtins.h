#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

# define EXIT_ERROR "bash: exit: "
# define EXIT_TOO_MANY "exit\nbash: exit: too many arguments\n"
# define ERR_NUM_ARG ": numeric argument required\n"
# define ENV_TOO_MANY "‘: No such file or directory\n\
env: use -[v]S to pass options in shebang lines\n"
# define ERR_ENV "env: ‘"
# define ENV_NO_FILE "No such file or directory\n"

// ft_exit.c
int		ft_exit(t_data *data, t_cmd *cmd);

// ft_echo.c
void	ft_echo(t_cmd *cmd);

// ft_env.c
void	ft_env(t_data *data, t_cmd *cmd);

// ft_pwd.c
void	ft_pwd(t_data *data, t_cmd *cmd);

// ft_cd.c

void	ft_cd(t_data *data, t_cmd *cmd);

#endif
