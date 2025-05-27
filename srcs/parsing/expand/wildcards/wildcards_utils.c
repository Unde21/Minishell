#include "minishell.h"
#include "parsing.h"
#include <stdlib.h>
// #include <sys/type.h>
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

int	get_nb_file(char *wildcards)
{
	DIR				*current_dir;
	struct dirent	*read_file;
	int				nb_file;

	nb_file = 0;
	current_dir = opendir(CURRENT_DIRECTORY);
	if (current_dir == NULL)
	{
		ft_dprintf(2, ERR_OP_DIR);
		return (-1);
	}
	read_file = readdir(current_dir);
	while (read_file != NULL)
	{
		if (read_file->d_name[0] != '.'
			&& check_match(read_file->d_name, wildcards) == true)
			++nb_file;
		read_file = readdir(current_dir);
	}
	if (closedir(current_dir) != 0) // a voir si exit si close fail
	{
		ft_dprintf(2, ERR_CLOSE_DIR);
		return (-2);
	}
	return (nb_file);
}
