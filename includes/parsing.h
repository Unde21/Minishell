#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"
# include <readline/history.h>
# include <readline/readline.h>

# define ERR_MALLOC "malloc failed\n"
// Modifier les msg d error en fonction de bash
# define MISS_DBLE_QUOTE "syntax error: missing closing double quote\n"
# define MISS_SNGL_QUOTE "syntax error: missing closing single quote\n"
# define ERR_MULTIPLE_PIPE "syntax error: multiple pipe in a row\n"
# define ERR_PIPE "syntax error near unexpected token `|'\n"
# define ERR_NO_FILE "syntax error: missing file after redirection\n"
# define ERR_OP_DIR "error: failed to open directory\n"
# define ERR_CLOSE_DIR "error: failed to close directory\n"
# define ASCII_DBLE_QUOTE 34
# define ASCII_SNGL_QUOTE 39
# define ASCII_DOLLAR 36
# define ASCII_UNDERSCORE 95
# define NO_QUOTE 0

struct s_cmd;
struct s_data;
struct s_token;
struct s_token_lst;
enum e_token_type;

typedef struct s_cmd		t_cmd;
typedef struct s_data		t_data;
typedef struct s_token		t_token;
typedef struct s_token_lst	t_token_lst;
typedef enum e_token_type	t_token_type;

// parsing.c
bool						parsing(t_data *data);

// handle_token.c
t_token						*new_token(char *content, t_token_type type);
bool						handle_token(t_data *data, char *input,
								t_token_lst *tokens, t_token *current);

// handle_word.c
size_t						handle_word(char *input, t_token **new,
								t_data *data);

// handle_word_utils.c
bool						is_special_operator(char input, int is_quote);
int							save_quote(char input);
void						new_node_word(t_token **new, char *word,
								int is_quote, t_data *data);

// create_node_for_token.c
size_t						new_node_pipes(t_token **new, t_data *data);
size_t						new_node_redir_out(t_token **new, t_data *data);
size_t						new_node_redir_in(t_token **new, t_data *data);
size_t						new_node_here_doc(t_token **new, t_data *data);
size_t						new_node_append(t_token **new, t_data *data);

// fill_cmd_lst.c
bool						get_cmd_args(t_token *current, t_cmd **cmd);

// utils.c
bool						is_redir_type(t_token_type type);
void						skip_quote_dollar(char **input, int is_quote,
								size_t *word_size, int *count_quote);
char						*ft_strjoin_and_free(char *s1, char *s2);

// parser.c
bool						parser(t_data *data, t_cmd **cmd);

// fill_special_operator_cmd.c
bool						add_special_operator_to_cmd(t_token *current,
								t_cmd *cmd);
bool						fill_cmd_special_operator(t_token **current,
								t_cmd *current_cmd);

// handle_expansion.c
bool						handle_expansion(t_data *data, t_cmd *cmd);

// expand.c
void						expand_tokens(t_cmd *current);

// expand_utils.c
void						join_with_expand(t_data *data, char **expanded,
								char *s, size_t *i);

// expand_wildcards
void						join_wildcards(t_data *data, char **expanded,
								char *s, size_t *i);

// remove_quote.c
bool						remove_quote(t_args *args);

// convert_lst_to_array.c
bool						convert_lst_to_array(t_cmd *cmd);
char						**lst_to_array(t_args *args, size_t nb_args);

#endif
