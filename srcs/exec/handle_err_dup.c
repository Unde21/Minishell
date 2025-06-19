/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_err_dup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samaouch <samaouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 01:30:37 by samaouch          #+#    #+#             */
/*   Updated: 2025/06/20 01:30:38 by samaouch         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include <unistd.h>

bool	err_dup_parent(t_data *data, t_cmd *cmd, int save_stdin,
		int save_stdout)
{
	if (save_stdin != -1)
		close(save_stdin);
	if (save_stdout != -1)
		close(save_stdout);
	if (cmd->fd_in != -1)
		close(cmd->fd_in);
	if (cmd->fd_out != -1)
		close(cmd->fd_out);
	print_err_false(ERR_DUP);
	data->return_value = 1;
	return (false);
}
