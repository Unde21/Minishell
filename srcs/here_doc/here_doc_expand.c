#include "parsing.h"

bool	is_expand_here_doc(char *file_name)
{
	size_t	i;

	i = 0;
	if (file_name == NULL)
		return (false);
	if (wich_quote(file_name) != NO_QUOTE)
		return (false);
	while (file_name[i])
	{
		if (file_name[i] == ASCII_DOLLAR)
			return (true);
		++i;
	}
	return (false);
}
