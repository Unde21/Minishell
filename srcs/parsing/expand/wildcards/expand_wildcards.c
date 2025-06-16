#include "minishell.h"
#include "parsing.h"
#include <dirent.h>
#include <errno.h>
#include <stdlib.h>

static int	bash_strcmp(const char *s1, const char *s2)
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

static char	*sort_file_name(char *cpy_file)
{
	char	**split_file;
	int		i;
	int		j;

	i = -1;
	split_file = ft_split(cpy_file, '/');
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
	cpy_file = ft_strjoin_and_free_array(split_file, ft_strlen(cpy_file),
			cpy_file);
	return (cpy_file);
}

static void	expand_wildcards(char **expanded, char *cpy_file, char *wildcards,
		size_t len_expanded)
{
	cpy_file = sort_file_name(cpy_file);
	if (cpy_file == NULL)
	{
		free(wildcards);
		ft_dprintf(2, ERR_MALLOC);
		*expanded = NULL;
		return ;
	}
	*expanded = ft_strjoin_and_free(*expanded, cpy_file);
	if (*expanded == NULL)
	{
		free(cpy_file);
		free(wildcards);
		return ;
	}
	if (len_expanded == ft_strlen(*expanded))
		*expanded = ft_strjoin_and_free(*expanded, wildcards);
	free(cpy_file);
}

void	join_wildcards(t_data *data, char **expanded, char *s, size_t *i)
{
	char	*wildcards;
	size_t	len_expanded;
	char	*cpy_file;

	len_expanded = ft_strlen(*expanded);
	wildcards = get_pattern(s, *i);
	if (wildcards == NULL)
	{
		*expanded = NULL;
		return ;
	}
	cpy_file = create_cpy_pattern(data, expanded, wildcards);
	if (cpy_file == NULL)
	{
		free(wildcards);
		return ;
	}
	expand_wildcards(expanded, cpy_file, wildcards, len_expanded);
	*i += ft_strlen(wildcards);
	free(wildcards);
}
