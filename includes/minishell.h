/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erbuffet <erbuffet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 13:40:58 by samaouch          #+#    #+#             */
/*   Updated: 2025/05/02 15:53:52 by erbuffet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "exec.h"
# include "libft.h"
# include "parsing.h"
# include <stdio.h>

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
	t_token_type	type;
	struct s_token	*next;
}					t_token;

typedef struct s_token_lst
{
	t_token			*head;
	t_token			*tail;
}					t_token_lst;

typedef struct s_redir
{
	t_token_type	type;
	char			*file;
	// bool			need_expand; // a voir
	struct s_redir	*next;
}					t_redir;

typedef struct s_args
{
	char			*content;
	bool			is_quote;
	bool			need_expand;
}					t_args;

typedef struct s_cmd
{
	t_args			*args;
	size_t			nb_args;
	t_redir			*redir;
	struct s_cmd	*next;
}					t_cmd;
typedef struct s_env
{
	char			*key;
	char			*value;
	char			*full_line;

	struct s_env	*next;
}					t_env;

typedef struct s_data
{
	char			*line_read;
	int				ac;
	char			*name_infile;
	char			*name_outfile;
	char			**av;
	char			**env;
	t_env			*listed_env;
	t_cmd			*cmd;
	t_redir			*redir;
	t_token			*token;
	t_token_lst		*token_lst;
}					t_data;

// init.c
void				init_data(t_data *data, int ac, char **av, char **env);
bool				init_lst(t_data *data);
bool				init_cmd_args(t_cmd *cmd);

// utils.c
bool				print_err(char *str_error);

// TODO delete
void				print_lst(t_token *token);
void				print_lst_cmd(t_cmd *cmd);
void				print_lst_cmd_expand(t_cmd *cmd);

void				clear_token(t_token *lst);
void				clear_cmd(t_cmd *cmd);
void				free_all(char **str);
int					wich_quote(char *input);

#endif
