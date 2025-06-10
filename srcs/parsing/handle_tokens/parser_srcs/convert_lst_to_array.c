#include "minishell.h"
#include "parsing.h"
#include <stdlib.h>

// bool	convert_lst_to_array(t_cmd *cmd)
// {
// 	t_cmd	*current;

// 	current = cmd;
// 	while (current)
// 	{
// 		current->params = lst_to_array(current->args, current->nb_args);
// 		if (current->params == NULL)
// 			return (false);
// 		current = current->next;
// 	}
// 	return (true);
// }

// static char	**get_nb_params(char *s, size_t *count_args)
// {
// 	char	**split_args;

// 	split_args = ft_split(s, ' ');
// 	if (split_args == NULL)
// 	{
// 		free(s);
// 		ft_dprintf(2, ERR_MALLOC);
// 		return (NULL);
// 	}
// 	free(s);
// 	while (split_args[*count_args])
// 		++(*count_args);
// 	return (split_args);
// }

// static char	*join_args(t_args *args, size_t nb_args)
// {
// 	char	*join;
// 	size_t	i;

// 	i = 1;
// 	join = args[0].content;
// 	join = ft_strjoin_and_free(join, " ");
// 	args[0].content = NULL;
// 	while (i < nb_args)
// 	{
// 		join = ft_strjoin_and_free(join, args[i].content);
// 		if (join == NULL)
// 		{
// 			ft_dprintf(2, ERR_MALLOC);
// 			return (NULL);
// 		}
// 		join = ft_strjoin_and_free(join, " ");
// 		++i;
// 	}
// 	return (join);
// }

// static char	**cpy_args(char **split_args, char **params, size_t count_args)
// {
// 	size_t	i;

// 	i = 0;
// 	while (split_args[i] && i < count_args)
// 	{
// 		params[i] = ft_strdup(split_args[i]);
// 		if (params == NULL)
// 		{
// 			ft_dprintf(2, ERR_MALLOC);
// 			return (NULL);
// 		}
// 		++i;
// 	}
// 	params[i] = NULL;
// 	return (params);
// }

// char	**lst_to_array(t_args *args, size_t nb_args)
// {
// 	char	**split_args;
// 	char	**params;
// 	size_t	count_args;
// 	char	*s;

// 	count_args = 0;
// 	s = join_args(args, nb_args);
// 	if (s == NULL)
// 		return (NULL);
// 	split_args = get_nb_params(s, &count_args);
// 	if (split_args == NULL)
// 		return (NULL);
// 	params = malloc(sizeof(char *) * (count_args + 1));
// 	if (params == NULL)
// 	{
// 		free_all(split_args);
// 		ft_dprintf(2, ERR_MALLOC);
// 		return (NULL);
// 	}
// 	params = cpy_args(split_args, params, count_args);
// 	free_all(split_args);
// 	return (params);
// }
