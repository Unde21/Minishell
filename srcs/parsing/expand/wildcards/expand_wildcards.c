#include "minishell.h"
#include "parsing.h"
#include <stdlib.h>
#include <errno.h>
#include <dirent.h>

static bool	is_file_name_valid(char *file_name, char *wildcards,
	char **cpy_file, int *nb_file)
{
	if (file_name[0] != '.' && check_match(file_name, wildcards) == true)
	{
		*cpy_file = ft_strjoin_and_free(*cpy_file, file_name);
		if (*cpy_file == NULL)
			return (false);
		if (nb_file > 0)
		{
			--*nb_file;
			*cpy_file = ft_strjoin_and_free(*cpy_file, " ");
			if (*cpy_file == NULL)
				return (false);
		}
	}
	return (true);
}

static char	*expand_wildcards_loop(char *wildcards, int nb_file, char *cpy_file,
		DIR *current_dir)
{
	size_t			index;
	struct dirent	*read_file;

	index = 0;
	errno = 0;
	while (1)
	{
		read_file = readdir(current_dir);
		if (errno != 0)
		{
			ft_dprintf(2, ERR_READDIR);
			return (NULL);
		}
		else if (read_file == NULL)
			break ;
		if (is_file_name_valid(read_file->d_name,
				wildcards, &cpy_file, &nb_file) == false)
			return (NULL);
	}
	return (cpy_file);
}

char	*expand_wildcards(char *wildcards, int nb_file, char *cpy_file)
{
	DIR			*current_dir;

	current_dir = NULL;
	if (open_dir(&current_dir) == false)
		return (NULL);
	cpy_file = expand_wildcards_loop(wildcards, nb_file, cpy_file, current_dir);
	if (close_dir(&current_dir) == false)
		return (NULL);
	return (cpy_file);
}

static char	*sort_file_name(char *cpy_file)
{
	char	**split_file;
	int		i;
	int		j;
	char	*tmp;

	i = -1;
	tmp = NULL;
	split_file = ft_split(cpy_file, ' ');
	if (split_file == NULL)
	{
		ft_dprintf(2, ERR_MALLOC);
		return (NULL);
	}
	while (split_file[++i])
	{
		j = i;
		while (split_file[++j])
		{
			if (bash_strcmp(split_file[i], split_file[j]) > 0)
				ft_swap_array(&split_file[i], &split_file[j]);
		}
	}
	cpy_file = ft_strjoin_and_free_array(split_file, ft_strlen(cpy_file));
	return (cpy_file);
}

void	join_wildcards(t_data *data, char **expanded, char *s, size_t *i)
{
	char		*wildcards;
	size_t		len_expanded;
	char		*cpy_file;

	len_expanded = ft_strlen(*expanded);
	wildcards = get_pattern(s, *i);
	if (wildcards == NULL)
	{
		*expanded = NULL;
		return ;
	}
	cpy_file = create_cpy_pattern(data, expanded, wildcards);
	if (cpy_file == NULL)
		return ;
	cpy_file = sort_file_name(cpy_file);
	if (cpy_file == NULL)
	{
		ft_dprintf(2, ERR_MALLOC);
		return ;
	}
	*expanded = ft_strjoin_and_free(*expanded, cpy_file);
	free(cpy_file);
	*i = ft_strlen(wildcards);
	if (len_expanded == ft_strlen(*expanded))
		*expanded = ft_strjoin_and_free(*expanded, wildcards);
}
