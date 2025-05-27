#ifndef EXEC_H
# define EXEC_H

typedef struct s_env	t_env;
typedef struct s_cmd	t_cmd;

# include "minishell.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

//// init ////
bool					init_child(t_cmd *cmd, char *path_cmd, char **env);

void					init_listed_env(t_data *data);
char					*heredoc(char *limiter);

//// add_node ////
t_env					*create_node(t_data *data, int i);
void					add_back(t_env *new_node, t_env **stack);

////  isit   ////
char					*wich_redir(t_cmd *cmd);
bool					is_heredoc(t_data *data);
bool					is_cmd(t_data *data, char *cmd);
bool					is_pipe(t_data *data);
//// getters ////
char					*get_path_cmd(char **params);
int						get_list_size(t_data *data);
char					*get_key(char *env);
char					*get_limiter(t_cmd *cmd);
char					*get_random_name(char *here_doc);

//// exec ////
bool					exec_init(t_data *data);

//// utils ////
void					free_listed_env(t_data *data);
void					close_fd(t_cmd *cmd);

#endif