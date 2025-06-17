#include "minishell.h"
#include "parsing.h"
#include <dirent.h>
#include <errno.h>
#include <stdlib.h>

int	get_nb_file(char *wildcards)
{
	DIR				*current_dir;
	struct dirent	*read_file;
	int				nb_file;

	nb_file = 0;
	errno = 0;
	current_dir = NULL;
	if (open_dir(&current_dir) == false)
		return (-1);
	read_file = readdir(current_dir);
	while (1)
	{
		read_file = readdir(current_dir);
		if (errno != 0)
			return (-3);
		else if (read_file == NULL)
			break ;
		if (read_file->d_name[0] != DOT && check_match(read_file->d_name,
				wildcards) == true)
			++nb_file;
	}
	if (close_dir(&current_dir) == false)
		return (-2);
	return (nb_file);
}

bool	close_dir(DIR **current_dir)
{
	if (closedir(*current_dir) != 0)
		return (print_err(ERR_CLOSE_DIR));
	return (true);
}

bool	open_dir(DIR **current_dir)
{
	*current_dir = opendir(CURRENT_DIRECTORY);
	if (*current_dir == NULL)
		return (print_err(ERR_OP_DIR));
	return (true);
}

bool	is_file_name_valid(char *file_name, char *wildcards, char **cpy_file,
		int *nb_file)
{
	if (file_name[0] != '.' && check_match(file_name, wildcards) == true)
	{
		*cpy_file = ft_strjoin_and_free(*cpy_file, file_name);
		if (*cpy_file == NULL)
			return (false);
		if (*nb_file > 0)
		{
			--*nb_file;
			*cpy_file = ft_strjoin_and_free(*cpy_file, "/");
			if (*cpy_file == NULL)
				return (false);
		}
	}
	return (true);
}

char	*ft_strjoin_and_free_array(char **tab, size_t len, char *cpy_file)
{
	char	*join;
	int		i;
	int		j;

	i = -1;
	join = malloc(sizeof(char) * (len + 1));
	if (join == NULL)
	{
		free(cpy_file);
		free_all(tab);
		return (NULL);
	}
	len = 0;
	while (tab[++i])
	{
		j = -1;
		while (tab[i][++j])
			join[len++] = tab[i][j];
		if (tab[i + 1] != NULL)
			join[len++] = ' ';
	}
	join[len] = '\0';
	free_all(tab);
	free(cpy_file);
	return (join);
}
