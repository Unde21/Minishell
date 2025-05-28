#include "minishell.h"
#include "parsing.h"
#include <stdlib.h>

static bool	is_quote_need_remove(char *src, size_t i)
{
	size_t	index;
	int		first_quote;

	index = 0;
	first_quote = NO_QUOTE;
	while (src[index])
	{
		if (src[index] == ASCII_DBLE_QUOTE)
		{
			first_quote = ASCII_DBLE_QUOTE;
			break ;
		}
		else if (src[index] == ASCII_SNGL_QUOTE)
		{
			first_quote = ASCII_SNGL_QUOTE;
			break ;
		}
		++index;
	}
	if (first_quote != src[i])
		return (false);
	return (true);
}

static char	*ft_strcdup(char *src)
{
	size_t	i;
	size_t	j;
	size_t	len_s;
	char	*dup;

	i = 0;
	j = 0;
	len_s = ft_strlen(src) - 2;
	ft_printf("len : %d\n", (int)len_s);
	dup = malloc(sizeof(char) * (len_s + 1));
	if (dup == NULL)
		return (NULL);
	while (src[i])
	{
		if (is_quote_need_remove(src, i) == false)
		{
			dup[j] = src[i];
			++j;
		}
		++i;
	}
	dup[j] = '\0';
	return (dup);
}

bool	remove_quote(t_args *args)
{
	size_t	i;
	char	*dup;

	dup = NULL;
	i = 0;
	ft_printf("args : %s\n", args->content);
	if (wich_quote(args->content) != NO_QUOTE)
	{
		dup = ft_strcdup(args->content);
		if (dup == NULL)
		{
			print_err(ERR_MALLOC);
			return (false);
		}
		free(args->content);
		args->content = dup;
	}
	return (true);
}




