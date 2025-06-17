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

void	reset(t_env *listed_env);
void	ft_export(t_data *data);
int		lst_size(t_env *head);
int		ft_exit(t_data *data, t_cmd *cmd);
int		export_type(t_data *data, char *params, t_env *listed_env);
bool	is_key_valid(t_data *data, char *params);
bool	ft_unset(t_data *data, t_env **listed_env, t_cmd *cmd);
bool	ft_pwd(t_data *data);
bool	ft_env(t_data *data, t_cmd *cmd);
bool	ft_echo(t_cmd *cmd);
bool	ft_cd(t_data *data, t_cmd *cmd);
bool	export_new(t_env *listed_env, char *params);
bool	display_error(t_data *data, char *params);
bool	append_export(char *key, t_env *listed_env, char *params);

#endif
