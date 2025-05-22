#include "minishell.h"
#include "parsing.h"
#include <stdlib.h>
// #include <sys/type.h>
#include <dirent.h>

static bool	check_match(char *file_name, char *wildcards)
{
	if (*wildcards == '\0' && *file_name == '\0')
		return (true);
	if (*wildcards == '*')
	{
		while (*wildcards == '*')
			++wildcards;
		if (!*wildcards)
			return (true);
		while (*file_name)
		{
			if (check_match(file_name, wildcards))
				return (true);
			++file_name;
		}
		return (check_match(file_name, wildcards));
	}
	if (*wildcards == *file_name)
		return (check_match(file_name + 1, wildcards + 1));
	return (false);
}

static char	*get_pattern(char *s, size_t i)
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

static int	get_nb_file(void) // a voir si exit si close fail
{
	DIR	*current_dir;
	struct dirent	*read_file;
	int	nb_file;
	
	nb_file = 0;
	current_dir = opendir(".");
	if (current_dir == NULL)
	{
		ft_dprintf(2, ERR_OP_DIR);
		return (-1);
	}
	read_file = readdir(current_dir);
	while (read_file != NULL)
	{
		++nb_file;
		read_file = readdir(current_dir);
	}
	if (closedir(current_dir) != 0)
	{
		ft_dprintf(2, ERR_CLOSE_DIR);
		return (-2);
	}
	return (nb_file);
}

// voir si faut secur readdir etc.. 
static void	expand_wildcards(char *wildcards, char **expanded, int nb_file)
{
	DIR			*current_dir;
	struct dirent	*read_file;
	size_t	index;

	index = 0;
	current_dir = opendir(".");
	if (current_dir == NULL)
	{
		ft_dprintf(2, ERR_OP_DIR);
		*expanded = NULL;
		return ;
	}
	while (index < (size_t)nb_file)
	{
		read_file = readdir(current_dir);
		if (read_file->d_name[0] != '.')
		{
			if (check_match(read_file->d_name, wildcards) == true)
			{
				*expanded = ft_strjoin_and_free(*expanded, read_file->d_name);
				if (index < (size_t)nb_file - 1)
					*expanded = ft_strjoin_and_free(*expanded, " ");
			}
		}
		++index;
	}
	if (closedir(current_dir) != 0)
	{
		ft_dprintf(2, ERR_CLOSE_DIR);
		*expanded = NULL;
		return ;
	}
}

//TODO a voir si faut open ici plutot que dans expand_wildcards
void	join_wildcards(t_data *data, char **expanded, char *s, size_t *i)
{
	int			nb_file;
	char		*wildcards;
	size_t		len_expanded;

	(void)data;
	len_expanded = ft_strlen(*expanded);
	wildcards = get_pattern(s, *i);
	if (wildcards == NULL)
	{
		*expanded = NULL;
		return ;
	}
	nb_file = get_nb_file();
	if (nb_file < 0) // a voir si exit si close fail -> changer get_nb_file en booleen
	{
		*expanded = NULL;
		return ;
	}
	expand_wildcards(wildcards, expanded, nb_file);
	*i = ft_strlen(wildcards);
	if (len_expanded == ft_strlen(*expanded))
		*expanded = ft_strjoin_and_free(*expanded, wildcards);
}
