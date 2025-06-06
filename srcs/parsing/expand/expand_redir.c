#include "minishell.h"
#include "parsing.h"
#include <stdlib.h>

static void	expand_loop(char *s, char **expanded, t_data *data, size_t *i)
{
	if (s[*i] == ASCII_DOLLAR && s[*i + 1] != ASCII_DOLLAR)
	{
		if (s[*i + 1] == '?')
			join_return_value(expanded, i, data->return_value);
		else
			join_with_expand_file(data, expanded, s, i);
	}
	else if (s[*i] == ASCII_DBLE_QUOTE)
		++(*i);
	else
		join_without_expand(expanded, s[*i], i);
}

static char	*expand(char *s, char *expanded, t_data *data)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		expand_loop(s, &expanded, data, &i);
		if (expanded == NULL)
			break ;
		else if (data->is_ambiguous == true)
		{
			ft_dprintf(2, PRINT_BASH);
			ft_dprintf(2, " %s: ", s);
			ft_dprintf(2, ERR_AMBIGUOUS);
			break ;
		}
	}
	free(s);
	if (expanded == NULL)
		return (NULL);
	return (expanded);
}

static bool	replace_file_name(t_data *data, char **file_name)
{
	char	*expanded;

	expanded = ft_calloc(sizeof(char), 1);
	if (expanded == NULL)
	{
		data->return_value = 1;
		ft_dprintf(2, ERR_MALLOC);
		return (false);
	}
	*file_name = expand(*file_name, expanded, data);
	if (*file_name == NULL)
	{
		data->return_value = 1;
		ft_dprintf(2, ERR_MALLOC);
		return (false);
	}
	if (data->is_ambiguous == true)
	{
		data->return_value = 1;
		return (false);
	}
	return (true);
}

static bool	is_expand(char *file_name)
{
	size_t	i;

	i = 0;
	if (file_name == NULL)
		return (false);
	if (file_name[i] == ASCII_SNGL_QUOTE)
		return (false);
	while (file_name[i])
	{
		if (file_name[i] == ASCII_DOLLAR)
			return (true);
		++i;
	}
	return (false);
}

bool	expand_redir(t_data *data, t_cmd *cmd)
{
	t_redir	*current_redir;

	current_redir = cmd->redir;
	while (current_redir != NULL)
	{
		if (current_redir->type != HERE_DOC
			&& is_expand(current_redir->file) == true)
		{
			if (replace_file_name(data, &current_redir->file) == false)
				return (false);
		}
		else if (remove_quote(data, &current_redir->file) == false)
			return (false);
		current_redir = current_redir->next;
	}
	return (true);
}
