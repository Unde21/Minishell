#include "minishell.h"
#include "parsing.h"
#include <stdlib.h>
#include <errno.h>
#include <dirent.h>

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
		if (read_file->d_name[0] != DOT
			&& check_match(read_file->d_name, wildcards) == true)
			++nb_file;
	}
	if (close_dir(&current_dir) == false)
		return (-2);
	return (nb_file);
}

bool	close_dir(DIR **current_dir)
{
	if (closedir(*current_dir) != 0)
	{
		ft_dprintf(2, ERR_CLOSE_DIR);
		return (false);
	}
	return (true);
}

bool	open_dir(DIR **current_dir)
{
	*current_dir = opendir(CURRENT_DIRECTORY);
	if (*current_dir == NULL)
	{
		ft_dprintf(2, ERR_OP_DIR);
		return (false);
	}
	return (true);
}

int	bash_strcmp(const char *s1, const char *s2)
{
	int				i;
	unsigned char	c1;
	unsigned char	c2;

	i = -1;
	while (s1[++i] && s2[i])
	{
		c1 = (unsigned char)s1[i];
		c2 = (unsigned char)s2[i];
		if (c1 != c2)
		{
			if (s1[i] >= 'A' && s1[i] <= 'Z')
				c1 = (unsigned char)(s1[i] + 32);
			if (s2[i] >= 'A' && s2[i] <= 'Z')
				c2 = (unsigned char)(s2[i] + 32);
			if (c1 == c2)
				continue ;
			if (c1 < c2)
				return (-1);
			else if (c1 > c2)
				return (1);
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		}
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

char	*ft_strjoin_and_free_array(char **tab, size_t len)
{
	char	*join;
	int		i;
	int		j;

	i = -1;
	join = malloc(sizeof(char) * (len + 1));
	if (join == NULL)
	{
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
	return (join);
}
