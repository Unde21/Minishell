#include "minishell.h"
#include "parsing.h"
#include <stdlib.h>
#include <errno.h>
#include <dirent.h>

bool	check_match(char *file_name, char *wildcards)
{
	if (*wildcards == '\0' && *file_name == '\0')
		return (true);
	if (*wildcards == WILDCARDS)
	{
		while (*wildcards == WILDCARDS)
			++wildcards;
		if (!*wildcards)
			return (true);
		while (*file_name)
		{
			if (check_match(file_name, wildcards) == true)
				return (true);
			++file_name;
		}
		return (check_match(file_name, wildcards));
	}
	if (*wildcards == *file_name)
		return (check_match(file_name + 1, wildcards + 1));
	return (false);
}

char	*get_pattern(char *s, size_t i)
{
	char	*wildcards;
	size_t	len_wildcards;
	size_t	j;

	len_wildcards = i;
	while (s[len_wildcards])
		++len_wildcards;
	wildcards = malloc(sizeof(char *) * (len_wildcards + 1));
	if (wildcards == NULL)
	{
		ft_dprintf(2, ERR_MALLOC);
		return (NULL);
	}
	j = 0;
	while (s[i])
	{
		wildcards[j] = s[i];
		++i;
		++j;
	}
	wildcards[j] = '\0';
	return (wildcards);
}

char	*create_cpy_pattern(t_data *data, char **expanded, char *wildcards)
{
	int		nb_file;
	char	*cpy_file;

	nb_file = get_nb_file(wildcards);
	if (nb_file < 0)
	{
		if (nb_file == -3)
			data->error_readdir = true;
		*expanded = NULL;
		return (NULL);
	}
	cpy_file = ft_strdup("");
	if (cpy_file == NULL)
	{
		ft_dprintf(2, ERR_MALLOC);
		*expanded = NULL;
		return (NULL);
	}
	cpy_file = expand_wildcards(wildcards, nb_file, cpy_file);
	if (cpy_file == NULL)
	{
		*expanded = NULL;
		return (NULL);
	}
	return (cpy_file);
}
