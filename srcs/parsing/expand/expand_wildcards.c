#include "minishell.h"
#include "parsing.h"
// #include <sys/type.h>
#include <dirent.h>

void	join_wildcards(t_data *data, char **expanded, char *s, size_t *i)
{
	DIR				*current_dir;
	struct dirent	*read_file;
	size_t			count_file;
	size_t			j;

	(void)data;
	(void)s;
	count_file = 0;
	j = 0;
	current_dir = opendir(".");
	if (current_dir == NULL)
	{
		ft_dprintf(2, ERR_OP_DIR);
		*expanded = NULL;
		return ;
	}
	read_file = readdir(current_dir);
	while (read_file != NULL)
	{
		++count_file;
		read_file = readdir(current_dir);
	}
	if (closedir(current_dir) != 0)
	{
		ft_dprintf(2, ERR_CLOSE_DIR);
		*expanded = NULL;
		return ;
	}
	current_dir = opendir(".");
	if (current_dir == NULL)
	{
		ft_dprintf(2, ERR_OP_DIR);
		*expanded = NULL;
		return ;
	}
	while (j < count_file)
	{
		read_file = readdir(current_dir);
		if (read_file->d_name[0] != '.')
		{
			*expanded = ft_strjoin_and_free(*expanded, read_file->d_name);
			if (j < count_file - 1)
				*expanded = ft_strjoin_and_free(*expanded, " ");
		}
		++j;
	}
	++(*i);
	if (closedir(current_dir) != 0)
	{
		ft_dprintf(2, ERR_CLOSE_DIR);
		*expanded = NULL;
		return ;
	}
}
