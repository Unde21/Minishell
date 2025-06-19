/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_array.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samaouch <samaouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 01:30:32 by samaouch          #+#    #+#             */
/*   Updated: 2025/06/20 01:30:33 by samaouch         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "parsing.h"
#include <stdlib.h>

static bool	fill_listed_env_to_array(t_data *data, t_env *head, int i)
{
	if (head->full_line != NULL)
	{
		data->env_array[i] = ft_strdup(head->full_line);
		if (data->env_array[i] == NULL)
		{
			free_delim(data->env_array, i);
			return (false);
		}
	}
	else
	{
		data->env_array[i] = ft_strdup("");
		if (data->env_array[i] == NULL)
		{
			free_delim(data->env_array, i);
			return (false);
		}
	}
	return (true);
}

char	**listed_env_to_array(t_data *data, t_env *listed_env)
{
	int		i;
	int		size;
	t_env	*head;

	i = 0;
	size = lst_size(listed_env);
	head = listed_env;
	data->env_array = malloc(sizeof(char *) * (size + 1));
	if (!data->env_array)
		return (NULL);
	data->env_array[size] = NULL;
	while (head)
	{
		if (fill_listed_env_to_array(data, head, i) == false)
			return (NULL);
		++i;
		head = head->next;
	}
	return (data->env_array);
}
