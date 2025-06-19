#include "minishell.h"
#include "parsing.h"
#include <dirent.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

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
	wildcards = malloc(sizeof(char) * (len_wildcards + 1));
	if (wildcards == NULL)
		return (NULL);
	j = 0;
	while (s[i])
		wildcards[j++] = s[i++];
	wildcards[j] = '\0';
	return (wildcards);
}

static char	*get_cpy_pattern_loop(char *wildcards, int nb_file, char *cpy_file,
		DIR *current_dir)
{
	struct dirent	*read_file;

	errno = 0;
	while (1)
	{
		read_file = readdir(current_dir);
		if (errno != 0)
		{
			free(cpy_file);
			ft_dprintf(STDERR_FILENO, ERR_READDIR);
			return (NULL);
		}
		else if (read_file == NULL)
			break ;
		if (is_file_name_valid(read_file->d_name, wildcards, &cpy_file,
				&nb_file) == false)
		{
			free(cpy_file);
			return (NULL);
		}
	}
	return (cpy_file);
}

static char	*get_cpy_pattern(char *wildcards, int nb_file, char *cpy_file)
{
	DIR	*current_dir;

	current_dir = NULL;
	if (open_dir(&current_dir) == false)
	{
		free(cpy_file);
		return (NULL);
	}
	cpy_file = get_cpy_pattern_loop(wildcards, nb_file, cpy_file, current_dir);
	if (close_dir(&current_dir) == false)
	{
		free(cpy_file);
		return (NULL);
	}
	return (cpy_file);
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
		return (NULL);
	cpy_file = get_cpy_pattern(wildcards, nb_file, cpy_file);
	if (cpy_file == NULL)
	{
		free(*expanded);
		*expanded = NULL;
		free(wildcards);
		return (NULL);
	}
	return (cpy_file);
}
