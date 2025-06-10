#ifndef EXEC_H
# define EXEC_H

# include "minishell.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_env	t_env;
typedef struct s_cmd	t_cmd;
//// init ////

void					init(t_data *data, char **path_cmd, int *return_value);
void					init_child(t_data *data, char *path_cmd, t_cmd *head);
char					*heredoc(char *limiter);

//// add_node ////
t_env					*create_node(t_data *data, int i);
void					add_back(t_env *new_node, t_env **stack);

//// getters ////
char					*get_path_cmd(char **params, char *path_cmd,
							int *return_value);
int						get_list_size(t_data *data);
char					*get_key(char *env);
char					*get_limiter(t_cmd *cmd);
char					*get_random_name(char *here_doc);

//// exec ////
void					exec_init(t_data *data);
void					wait_child(int *return_value);

//// utils ////
void					clear_exec(t_data *data);
void					free_listed_env(t_data *data);
void					close_fd(t_cmd *cmd);
bool					is_solo_builtin(char **params);
bool					is_child_builtin(char **params);
bool					child_builtin(t_data *data);
bool					solo_builtin(t_data *data);
bool					is_access_ok(char *path, int *return_value,
							char **path_cmd);

#endif