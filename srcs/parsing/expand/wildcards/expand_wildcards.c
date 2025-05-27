#include "minishell.h"
#include "parsing.h"
#include <stdlib.h>
// #include <sys/type.h>
#include <dirent.h>

static char *expand_wildcards_loop(char *wildcards, int nb_file, char *cpy_file,
		DIR *current_dir)
{
	size_t			index;
	struct dirent	*read_file;

	index = 0;
	read_file = readdir(current_dir);
	while (read_file != NULL)
	{
		if (read_file->d_name[0] != '.'
			&& check_match(read_file->d_name, wildcards) == true)
		{
			cpy_file = ft_strjoin_and_free(cpy_file, read_file->d_name);
			if (cpy_file == NULL)
				return (NULL);
			if (index < (size_t)nb_file - 1)
			{
				cpy_file = ft_strjoin_and_free(cpy_file, " ");
				if (cpy_file == NULL)
					return (NULL);
				++index;
			}
		}
		read_file = readdir(current_dir);
	}
	return (cpy_file);
}

// voir si faut secur readdir etc.. 
static char	*expand_wildcards(char *wildcards, char **expanded, int nb_file,
		char *cpy_file)
{
	DIR			*current_dir;

	(void)expanded;
	current_dir = opendir(CURRENT_DIRECTORY);
	if (current_dir == NULL)
	{
		ft_dprintf(2, ERR_OP_DIR);
		// *expanded = NULL;
		return (NULL);
	}
	cpy_file = expand_wildcards_loop(wildcards, nb_file, cpy_file, current_dir);
	if (closedir(current_dir) != 0)
	{
		ft_dprintf(2, ERR_CLOSE_DIR);
		// *expanded = NULL;
		return (NULL);
	}
	return (cpy_file);
}

char	*ft_strjoin_and_free_array(char **tab, size_t len)
{
	char	*join;
	size_t	i;
	size_t	j;
	size_t	index;

	i = 0;
	index = 0;
	join = malloc(sizeof(char) * (len + 1));
	if (join == NULL)
	{
		free_all(tab);
		return (NULL);
	}
	while (tab[i])
	{
		j = 0;
		while(tab[i][j])
		{
			join[index] = tab[i][j];
			++j;
			++index;
		}
		if (tab[i + 1] != NULL)
			join[index++] = ' ';
		++i;
	}
	join[index] = '\0';
	free_all(tab);
	return (join);
}

int	bash_strcmp(const char *s1, const char *s2)
{
	size_t	i;
	unsigned char c1;
	unsigned char c2;

	i = 0;
	while (s1[i] && s2[i])
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
			{
				++i;
				continue ;
			}
			if (c1 < c2)
				return (-1);
			else if (c1 > c2)
				return (1);
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		}
		++i;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

static char	*sort_file_name(char *cpy_file)
{
	char	**split_file;
	size_t	i;
	size_t	j;
	char	*tmp;

	i = 0;
	j = 0;
	tmp = NULL;
	split_file = ft_split(cpy_file, ' ');
	for (size_t x = 0; split_file[x]; x++)
		ft_printf("split_file first : '%s'\n", split_file[x]);
	if (split_file == NULL)
	{
		ft_dprintf(2, ERR_MALLOC);
		return (NULL);
	}
	while (split_file[i])
	{
		j = i + 1;
		while (split_file[j])
		{
			if (bash_strcmp(split_file[i], split_file[j]) > 0)
			{
				tmp = split_file[i];
				split_file[i] = split_file[j];
				split_file[j] = tmp;
			}
			++j;
		}
		++i;
	}
	for (size_t k = 0; split_file[k]; k++)
		ft_printf("split_file sorted : '%s'\n", split_file[k]);
	cpy_file = ft_strjoin_and_free_array(split_file, ft_strlen(cpy_file));
	if (cpy_file == NULL)
	{
		ft_dprintf(2, ERR_MALLOC);
		return (NULL);
	}
	return (cpy_file);
}
// includes libft main.c Makefile minishell README.md readline.supp srcs
//TODO a voir si faut open ici plutot que dans expand_wildcards
void	join_wildcards(char **expanded, char *s, size_t *i)
{
	int			nb_file;
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
	nb_file = get_nb_file(wildcards);
	if (nb_file < 0) // a voir si exit si close fail -> changer get_nb_file en booleen
	{
		*expanded = NULL;
		return ;
	}
	cpy_file = ft_strdup("");
	if (cpy_file == NULL)
	{
		ft_dprintf(2, ERR_MALLOC);
		*expanded = NULL;
		return ;
	}
	cpy_file = expand_wildcards(wildcards, expanded, nb_file, cpy_file);
	if (cpy_file == NULL)
	{
		*expanded = NULL;
		return ;
	}
	ft_printf("cpy_file : %s\n", cpy_file);
	cpy_file = sort_file_name(cpy_file);
	ft_printf("cpy_file sorted: %s\n", cpy_file);
	*expanded = ft_strjoin_and_free(*expanded, cpy_file);
	free(cpy_file);
	*i = ft_strlen(wildcards);
	if (len_expanded == ft_strlen(*expanded))
		*expanded = ft_strjoin_and_free(*expanded, wildcards);
}
