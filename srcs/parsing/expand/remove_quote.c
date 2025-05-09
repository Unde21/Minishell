#include "minishell.h"
#include "parsing.h"
#include <stdlib.h>

static char	*ft_strcdup(char *src)
{
	size_t	i;
	size_t	j;
	size_t	len_s;
	char	*dup;

	i = 1;
	j = 0;
	len_s = ft_strlen(src);
	dup = malloc(sizeof(char) * (len_s - 1));
	if (dup == NULL)
		return (NULL);
	while (src[i] && i < len_s - 1)
	{
		dup[j] = src[i];
		++i;
		++j;
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
	if (args->content[i] == ASCII_DBLE_QUOTE
		|| args->content[i] == ASCII_SNGL_QUOTE)
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
