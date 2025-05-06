#include "debug.h"

static void	print_token_type(int type, char *s)
{
	if (type == 0)
		ft_printf("\033[33m{%s}		TYPE: WORD\033[0m", s);
	else if (type == 1)
		ft_printf("\033[33m{%s}		TYPE: SNGL_QUOTE\033[0m", s);
	else if (type == 2)
		ft_printf("\033[33m{%s}		TYPE: DBLE_QUOTE\033[0m", s);
	else if (type == 3)
		ft_printf("\033[33m{%s}		TYPE: PIPE\033[0m", s);
	else if (type == 4)
		ft_printf("\033[33m{%s}		TYPE: REDIR_IN\033[0m", s);
	else if (type == 5)
		ft_printf("\033[33m{%s}		TYPE: REDIR_OUT\033[0m", s);
	else if (type == 6)
		ft_printf("\033[33m{%s}		TYPE: HERE_DOC\033[0m", s);
	else if (type == 7)
		ft_printf("\033[33m{%s}		TYPE: APPEND\033[0m", s);
}

void	print_lst(t_token *token)
{
	if (token == NULL)
		return ;
	ft_printf("%s", PRINT_TOKENIZER);
	while (token != NULL)
	{
		ft_printf("%s", START_SEP_LINE_TOKEN);
		print_token_type(token->type, token->content);
		ft_printf("%s", END_SEP_LINE_TOKEN);
		ft_printf("%s", NEXT_NODE);
		token = token->next;
	}
	ft_printf("%s", PRINT_NULL_TOKEN);
	ft_printf("%s", END_SEP_LINE_TOKEN);
}
