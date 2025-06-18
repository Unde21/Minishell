#ifndef EXEC_H
# define EXEC_H

# include "minishell.h"
# include <fcntl.h>

# define PROMPT_HERE_DOC "> "
# define ERR_OP_FD "error: failed to open file\n"
# define ERR_CREAT_PIPE "error: pipe failed\n"
# define ERR_FORK "error: fork failed\n"
# define ERR_DUP "error: dup failed\n"
# define ERR_EXECVE "error: execve failed\n"
# define QUIT "Quit (core dumped)\n"
# define WARNING_HEREDOC "> bash: warning: here-document \
delimited by end-of-file (wanted "

typedef struct s_env	t_env;
typedef struct s_cmd	t_cmd;

void	wait_child(pid_t last_pid, int *return_value);
void	free_listed_env(t_data *data);
void	execute_builtins(t_data *data);
void	execute_builtins(t_data *data);
void	exec(t_data *data);
void	close_fd(t_cmd *cmd, bool close_all_cmd);
void	clear_exec(t_data *data);
void	child(t_data *data, char *path_cmd, t_cmd *head);
void	add_back(t_env *new_node, t_env **stack);
t_env	*create_node(t_data *data, int i);
size_t	get_total_length(char **params);
size_t	get_size_cmd(t_cmd *cmd);
pid_t	init_child(t_data *data, t_cmd *head_cmd, char *path_cmd);
int		get_list_size(t_data *data);
char	*heredoc(t_data *data, t_redir *redir, char *limiter);
char	*get_value(t_data *data, char *params);
char	*get_random_name(char *here_doc);
char	*get_path_cmd(t_data *data, char **params, int *return_value);
char	*get_limiter(t_cmd *cmd);
char	*get_key(char *env);
char	**listed_env_to_array(t_data *data, t_env *listed_env);
bool	is_expand_here_doc(char *file_name);
bool	is_builtin(t_data *data);
bool	is_access_ok(char *path, int *return_value, char **params);
bool	init_redir(t_data *data, t_cmd *cmd);
bool	err_dup_parent(t_data *data, t_cmd *cmd,
			int save_stdin, int save_stdout);

#endif
