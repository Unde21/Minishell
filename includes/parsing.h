#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"
# include <dirent.h>
# include <readline/history.h>
# include <readline/readline.h>

# define ERR_MALLOC "error: malloc failed\n"
# define MISS_DBLE_QUOTE "syntax error: missing closing double quote\n"
# define MISS_SNGL_QUOTE "syntax error: missing closing single quote\n"
# define ERR_MULTIPLE_PIPE "syntax error: multiple pipe in a row\n"
# define ERR_PIPE "syntax error near unexpected token `|'\n"
# define ERR_NO_FILE "syntax error: missing file after redirection\n"
# define ERR_OP_DIR "error: failed to open directory\n"
# define ERR_CLOSE_DIR "error: failed to close directory\n"
# define ERR_READDIR "error: failed to read directory\n"
# define PRINT_BASH "bash:"
# define ERR_AMBIGUOUS "ambiguous redirect\n"
# define ASCII_DBLE_QUOTE 34
# define ASCII_SNGL_QUOTE 39
# define ASCII_DOLLAR 36
# define ASCII_UNDERSCORE 95
# define NO_QUOTE 0
# define WILDCARDS '*'
# define CURRENT_DIRECTORY "."
# define QUESTION_MARK '?'
# define DOT '.'
# define HEREDOC 42
# define NO_HERDOC 43

struct							s_cmd;
struct							s_data;
struct							s_token;
struct							s_token_lst;
enum							e_token_type;

typedef struct s_cmd			t_cmd;
typedef struct s_data			t_data;
typedef struct s_token			t_token;
typedef struct s_token_lst		t_token_lst;
typedef enum e_token_type		t_token_type;

// parsing.c
bool						parsing(t_data *data);

// handle_token.c
t_token						*new_token(char *content, t_token_type type);
bool						handle_token(t_data *data, char *input,
								t_token_lst *tokens, t_token *current);

// handle_word.c
size_t						handle_word(char *input, t_token **new,
								t_data *data, size_t word_size);

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
bool						parser(t_data *data, t_cmd **cmd, int prev_return_value);

// fill_special_operator_cmd.c
bool						add_special_operator_to_cmd(t_token *current,
								t_cmd *cmd);
bool						fill_cmd_special_operator(t_token **current,
								t_cmd *current_cmd);

// handle_expansion.c
bool						replace_env_variables(t_data *data, char **params,
								size_t i);
void						join_without_expand(char **expanded, char c,
								size_t *i);
void						join_return_value(char **expanded, size_t *i,
								int prev_return_value);

// expand_redir.c
bool						replace_file_name(t_data *data, char **file_name,
								int is_heredoc, t_redir *redir);
bool						expand_redir(t_data *data, t_cmd *cmd);
bool						is_expand_redir(char *file_name);

// expand_redir_utils.c
void						join_with_expand_file(t_data *data, char **expanded,
								char *s, size_t *i);

// expand_tokens.c
void						expand_tokens(t_cmd *current);
bool						handle_expansion(t_data *data, t_cmd *cmd);

// expand_utils.c
void						join_with_expand(t_data *data, char **expanded,
								char *s, size_t *i);
char						*get_var_name(char *s);
char						*dup_word_splitting(char *src);
// expand_wildcards
void						join_wildcards(t_data *data, char **expanded,
								char *s, size_t *i);

// wildcards_utils.c
int							get_nb_file(char *wildcards);
bool						open_dir(DIR **current_dir);
bool						close_dir(DIR **current_dir);
char						*ft_strjoin_and_free_array(char **tab, size_t len,
								char *cpy_file);
bool						is_file_name_valid(char *file_name, char *wildcards,
								char **cpy_file, int *nb_file);

// get_pattern.c
bool						check_match(char *file_name, char *wildcards);
char						*get_pattern(char *s, size_t i);
char						*create_cpy_pattern(t_data *data, char **expanded,
								char *wildcards);

// // remove_quote.c
bool						remove_quote(t_data *data, char **params);

// split_params.c
bool						split_wildcards_file(t_cmd *cmd);

// split_params_utils.c
void						free_delim(char **s, size_t delim);
void						count_params(char **params, size_t *len);
bool						need_split_params(t_cmd *cmd, char **params);

// split_after_expand.c
bool						handle_split_expand(t_cmd *cmd);

// split_after_expand_utils.c
char						**ft_split_with_charset(char *s);
void						count_params_expand(char **params, size_t *len);

#endif
