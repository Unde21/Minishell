/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samaouch <samaouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 12:47:49 by samaouch          #+#    #+#             */
/*   Updated: 2025/05/16 14:51:02 by samaouch         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_H
# define DEBUG_H

# include "minishell.h"
# include "parsing.h"

# ifndef DEBUG_VALUE
#  define DEBUG_VALUE 0
# endif

// print_tokenizer
# define PRINT_TOKENIZER "\n\033[37;45mPRINT TOKENISER:\033[0m\n\n"
# define PRINT_NULL_TOKEN "\033[35m==========================\
===============================================\n			      \
\033[42;42mNULL\033[0m"
# define START_SEP_LINE_TOKEN "\033[35m=========================\
================================================\033[0m\n"
# define END_SEP_LINE_TOKEN "\n\033[35m==============================\
===========================================\033[0m\n"
# define NEXT_NODE "       				|\n      				v\n"

//print_parser
# define PRINT_PARSER "\n\n\n\033[31;44mPRINT PARSER:\033[0m\n\n"
# define START_SEP_LINE_PARSER "\033[34m============================\
=============================================\033[0m\n"
# define EXPAND_YES "  \033[32m--> need_expand: Yes\033[0m"
# define EXPAND_NO "  \033[32m--> need_expand: No\033[0m"
# define END_SEP_LINE_PARSER "\n\033[34m===========================\
==============================================\033[0m\n"
# define PRINT_NULL_PARSER "\033[34m=============================\
============================================\033[0m\n			       \
\033[42;42mNULL\033[0m"
# define PARSER_REDIR_IN "\033[32m	=> REDIR_IN\033[0m"
# define PARSER_REDIR_OUT "\033[32m	=> REDIR_OUT\033[0m"
# define PARSER_HERE_DOC "\033[32m	=> HERE_DOC\033[0m"
# define PARSER_APPEND "\033[32m	=> APPEND\033[0m"

//print_expand
# define PRINT_EXPAND "\n\n\n\033[35;43mPRINT PARSER WITH EXPAND:\033[0m\n\n"
# define START_SEP_LINE_EXPAND "\033[33m=============================\
============================================\033[0m\n"
# define EXPAND_REDIR_IN "\033[35m	=> REDIR_IN\033[0m"
# define EXPAND_REDIR_OUT "\033[35m	=> REDIR_OUT\033[0m"
# define EXPAND_HERE_DOC "\033[35m	=> HERE_DOC\033[0m"
# define EXPAND_APPEND "\033[35m	=> APPEND\033[0m"
# define END_SEP_LINE_EXPAND "\n\033[33m=============================\
============================================\033[0m\n"
# define PRINT_NULL_EXPAND "\033[33m=============================\
============================================\033[0m\n			       \
\033[42;42mNULL\033[0m"

//print_.c
void	print_lst(t_token *token);
void	print_lst_cmd(t_cmd *cmd);
void	print_lst_cmd_expand(t_cmd *cmd);

#endif
