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

////////////////////////////
///////* list parsing */////
////////////////////////////
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
	char			*content;
	bool			in_list;
	t_token_type	type;
	struct s_token	*next;
}					t_token;

typedef struct s_token_lst
{
	t_token			*head;
	t_token			*tail;
}					t_token_lst;
////////////////////////////////

///////////////////////////
/////* list global *///////
///////////////////////////
typedef struct s_redir
{
	t_token_type	type;
	bool			is_ambiguous;
	char			*file;
	struct s_redir	*next;
}					t_redir;

typedef struct s_args
{
	char			*content;
	bool			is_quote;
	bool			need_expand;
	bool			is_wildcards;
}					t_args;

typedef struct s_cmd
{
	t_args			*args;
	char			**params;
	size_t			nb_args;
	t_redir			*redir;
	int				pipe_fd[2];
	int				fd_in;
	int				fd_out;
	struct s_cmd	*next;
}					t_cmd;
////////////////////////////

////////////////////////////
///////* list exec *////////
////////////////////////////
typedef struct s_env
{
	char			*key;
	char			*value;
	char			*full_line;
	int				printed;

	struct s_env	*next;
}					t_env;
/////////////////////////////

//////////////////////////
/////* main structur *////
//////////////////////////
typedef struct s_data
{
	char			*line_read;
	char			*ambiguous_file;
	int				ac;
	int				return_value;
	char			*name_infile;
	char			*name_outfile;
	char			**av;
	char			**env;
	bool			error_readdir;
	bool			is_ambiguous;
	bool			had_space_before;
	int				last_type;
	t_env			*listed_env;
	t_cmd			*cmd;
	t_redir			*redir;
	t_token			*token;
	t_token_lst		*token_lst;
}					t_data;
////////////////////////////

extern int			g_return_value;

// init.c
void				init_listed_env(t_data *data);

void				init_data(t_data *data, int ac, char **av, char **env);
bool				init_lst(t_data *data);
bool				init_cmd_args(t_cmd *cmd);

// utils.c
bool				print_err(char *str_error);
void				reset_g_return_value(t_data *data);
void				print_access_error(char *params, t_data *data);
void				print_ambiguous(char *s);

// clear_data.c
void				clear_token(t_token *lst);
void				clear_cmd(t_cmd *cmd);
void				free_all(char **str);
int					wich_quote(char *input);

// get_input.c
void				get_input(t_data *data);
void				clear_all_data(t_data *data);

// get_prompt.c
void				get_prompt(t_data *data, char **prompt);

// handle_signal.c
int					do_nothing(void);
void				set_signal_action(void);
void				reset_signal(void);
void	set_signal_action_child(void);

#endif
