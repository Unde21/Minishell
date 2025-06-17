#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

# define EXIT_ERROR "bash: exit: "
# define EXIT_TOO_MANY "exit\nbash: exit: too many arguments\n"
# define ERR_NUM_ARG ": numeric argument required\n"
# define ENV_TOO_MANY \
	"‘: No such file or directory\n\
env: use -[v]S to pass options in shebang lines\n"
# define ERR_ENV "env: ‘"
# define ENV_NO_FILE "No such file or directory\n"
# define CD_HOME "HOME"
# define CD_ERR "bash: cd: "
# define CD_NO_DIR "No such file or directory\n"
# define ERR_PWD "pwd: No such file or directory\n"
# define OLDPWD "OLDPWD"
# define PWD "PWD"
# define ERR_EXPORT ": not a valid identifier\n"

// ft_exit.c
int		ft_exit(t_data *data, t_cmd *cmd);

// ft_echo.c
void	ft_echo(t_cmd *cmd);

// ft_env.c
void	ft_env(t_data *data, t_cmd *cmd);

// ft_pwd.c
void	ft_pwd(t_data *data);

// ft_cd.c
void	ft_cd(t_data *data, t_cmd *cmd);

// cd_utils.c
void	display_error(t_data *data, char *params);

// ft_export.c
void	ft_export(t_data *data);

// export_utils.c
int	export_type(char *params, t_env *listed_env);
bool	is_key_valid(char *params);
int	lst_size(t_env *head);
void	reset(t_env *listed_env);
bool	append_export(t_env *listed_env, char *params);

// ft_unset.c
void	ft_unset(t_env **listed_env, t_cmd *cmd);

#endif
