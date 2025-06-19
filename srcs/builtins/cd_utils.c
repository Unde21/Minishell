/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samaouch <samaouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 01:29:36 by samaouch          #+#    #+#             */
/*   Updated: 2025/06/20 01:29:37 by samaouch         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

bool	display_error(t_data *data, char *params)
{
	ft_dprintf(2, CD_ERR);
	ft_dprintf(2, "%s: ", params);
	ft_dprintf(2, CD_NO_DIR);
	data->return_value = 1;
	return (true);
}
