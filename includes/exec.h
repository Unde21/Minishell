#ifndef EXEC_H
# define EXEC_H

typedef struct s_env	t_env;

# include "minishell.h"
# include "parsing.h"
# include <stdlib.h>

//// init ////
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
void					print_list(t_data *data);
void					print_env(t_data *data);

#endif