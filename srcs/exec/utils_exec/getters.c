/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erbuffet <erbuffet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 01:30:30 by samaouch          #+#    #+#             */
/*   Updated: 2025/06/20 12:10:12 by erbuffet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "parsing.h"
#include <stdlib.h>

char	*check_params(int *return_value, char *params, int *i)
{
	char	*value;

	(void)return_value;
	value = NULL;
	if (!params)
		return (NULL);
	while (params[*i] && params[*i] != '=')
		(*i)++;
	return (value);
}

char	*get_value(t_data *data, char *params)
{
	char	*value;
	int		start;
	int		len;
	int		i;

	i = 0;
	value = check_params(&data->return_value, params, &i);
	if (params[i] != '\0')
		start = i + 1;
	else
		start = i;
	len = 0;
	while (params[start + len])
		len++;
	value = malloc(sizeof(char) * (len + 1));
	if (!value)
	{
		data->return_value = 1;
		return (NULL);
	}
	i = 0;
	while (params[start])
		value[i++] = params[start++];
	value[i] = '\0';
	return (value);
}

char	*get_key(char *env)
{
	char	*key;
	int		i;

	key = NULL;
	i = 0;
	while (env[i] && env[i] != '=' && env[i] != '+')
		i++;
	if (env[i] == '\0')
	{
		key = ft_strdup(env);
		return (key);
	}
	key = malloc(sizeof(char) * (i + 1));
	if (!key)
		return (NULL);
	i = -1;
	while (env[++i] && env[i] != '=' && env[i] != '+')
		key[i] = env[i];
	key[i] = '\0';
	return (key);
}
