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

void	join_wildcards(t_data *data, char **expanded, char *s, size_t *i)
{
	DIR				*current_dir;
	struct dirent	*read_file;
	size_t			count_file;
	size_t			j;

	(void)data;
	size_t	k = *i;
	char	*wildcards;
	while (s[k])
	{
		++k;
	}
	wildcards = malloc(sizeof(char *) * (k + 1));
	if (wildcards == NULL)
	{
		ft_dprintf(2, ERR_MALLOC);
		*expanded = NULL;
		return ; 
	}
	k = *i;
	j = 0;
	while (s[k])
	{
		wildcards[j] = s[k];
		++k;
		++j;
	}
	wildcards[j] = '\0';
	ft_printf("pattern = %s\n", wildcards);
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
			if (check_match(read_file->d_name, wildcards) == true)
			{
				ft_printf("OK: %s\n", read_file->d_name);
				*expanded = ft_strjoin_and_free(*expanded, read_file->d_name);
				if (j < count_file - 1)
				*expanded = ft_strjoin_and_free(*expanded, " ");
			}
			else
				ft_printf("NOOOOOOO: %s\n", read_file->d_name);
		}
		++j;
	}
	*i = k;
	if (closedir(current_dir) != 0)
	{
		ft_dprintf(2, ERR_CLOSE_DIR);
		*expanded = NULL;
		return ;
	}
}
