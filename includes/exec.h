#ifndef EXEC_H
# define EXEC_H

typedef struct s_env	t_env;

# include "minishell.h"
# include <fcntl.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <unistd.h>

//// init ////
void					init_listed_env(t_data *data);
void					free_listed_env(t_data *data);
void					heredoc(char *limiter);

//// add_node ////
t_env					*create_node(t_data *data, int i);
void					add_back(t_env *new_node, t_env **stack);

//// getters ////
char					*get_key(char *env);
char					*get_limiter(t_data *data);
char					*get_random_name(char *here_doc);

//// exec ////
void					exec_init(t_data *data);

#endif