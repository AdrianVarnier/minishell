/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_all_cmd_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ali <ali@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 15:16:50 by ali               #+#    #+#             */
/*   Updated: 2022/02/03 19:23:24 by avarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_redir_error(t_cmd *cmd)
{
	if (cmd->redir_error == 1)
	{
		ft_putendl_fd("minishell: ambiguous redirect", 2);
		g_exit = 1;
		return (1);
	}
	return (0);
}

void	close_all_files(t_cmd *cmd)
{
	while (cmd != NULL)
	{
		if (cmd->input != 0)
			close(cmd->input);
		if (cmd->output != 1)
			close(cmd->output);
		cmd = cmd->next;
	}
}
