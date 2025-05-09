#ifndef EXEC_H
# define EXEC_H

typedef struct s_env	t_env;

# include "minishell.h"
# include "parsing.h"
# include <fcntl.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <unistd.h>

//// init ////
void					heredoc_init(t_data *data);
void					init_listed_env(t_data *data);
void					free_listed_env(t_data *data);
void					fill_listed_env(t_data *data);

//// add_node ////
t_env					*create_node(t_data *data, int i);
void					add_back(t_env *new_node, t_env **stack);

//// getters ////
char					*get_value(char *env);
char					*get_key(char *env);

//// debug ////
void					print_listed_env(t_data *data);
void					print_env(t_data *data);
void					print_lst(t_token *token, int t);
void					print_lst_cmd(t_cmd *cmd);
void					print_lst_cmd_expand(t_cmd *cmd);

//// exec ////

void					exec_init(t_data *data);

#endif