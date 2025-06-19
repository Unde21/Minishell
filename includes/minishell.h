#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"

# define CODE_SIGINT 130
# define BLUE "\001\033[1;34m\002"
# define RED "\001\033[1;31m\002"
# define GREEN "\001\033[1;32m\002"
# define END_BLUE "] \001\033[0m\002\001\033[1;34m\002"
# define END_COLOR "$ \001\033[0m\002"
# define CROSS "\001❌\002 ["
# define CHECK "\001✅\002 ["
# define PATH_ERROR "\001🤯\002 path_error: "

typedef enum e_token_type
{
	WORD,
	SNGL_QUOTE,
	DBLE_QUOTE,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	HERE_DOC,
	APPEND,
	NOTHING
}					t_token_type;

typedef struct s_token
{
	t_token_type	type;
	struct s_token	*next;
	char			*content;
	bool			in_list;
}					t_token;

typedef struct s_token_lst
{
	t_token			*tail;
	t_token			*head;
}					t_token_lst;

typedef struct s_redir
{
	t_token_type	type;
	struct s_redir	*next;
	char			*file;
	bool			is_ambiguous;
}					t_redir;

typedef struct s_args
{
	char			*content;
	bool			need_expand;
	bool			is_wildcards;
	bool			is_quote;
}					t_args;

typedef struct s_cmd
{
	t_redir			*redir;
	t_args			*args;
	struct s_cmd	*next;
	size_t			nb_args;
	int				pipe_fd[2];
	int				fd_out;
	int				fd_in;
	char			**params;
}					t_cmd;

typedef struct s_env
{
	struct s_env	*next;
	int				printed;
	char			*value;
	char			*key;
	char			*full_line;
}					t_env;

typedef struct s_data
{
	t_token_lst		*token_lst;
	t_token			*token;
	t_redir			*redir;
	t_env			*listed_env;
	t_cmd			*cmd;
	size_t			size_cmd;
	int				return_value;
	int				last_type;
	int				ac;
	int				save_stdin;
	int				save_stdout;
	char			*name_outfile;
	char			*name_infile;
	char			*line_read;
	char			*ambiguous_file;
	char			**env;
	char			**env_array;
	char			**av;
	bool			is_heredoc;
	bool			is_ambiguous;
	bool			had_space_before;
	bool			error_readdir;
}					t_data;

extern int			g_return_value;

void	signal_handler_child(int signal);
void	set_signal_action(void);
void	set_signal_action_child(void);
void	reset_signal(void);
void	reset_g_return_value(t_data *data);
void	print_ambiguous(char *s);
void	init_listed_env(t_data *data);
void	get_prompt(t_data *data, char **prompt);
void	get_input(t_data *data);
void	free_all(char **str);
void	clear_token(t_token *lst);
void	clear_cmd(t_data *data, t_cmd *cmd);
void	clear_all_data(t_data *data);
int		wich_quote(char *input);
int		do_nothing(void);
char	*print_err_null(char *str_error);
bool	print_err_false(char *str_error);
bool	init_lst(t_data *data);
bool	init_data(t_data *data, int ac, char **av, char **env);
bool	create_first_node(t_data *data, char *pwd);
bool	fill_next_node_minimal(t_data *data);
bool	init_cmd_args(t_cmd *cmd);
bool	minimal_env(t_data *data);

#endif
