/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@stduent.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 14:15:20 by avarnier          #+#    #+#             */
/*   Updated: 2021/12/16 14:24:37 by avarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	close_fd(t_cmd *cmd)
{
	if (cmd->input_type == PIPE)
		close(cmd->prev->output);
	if (cmd->output_type == PIPE)
		close(cmd->next->input);
}

void	redir(t_cmd *cmd)
{
	close_fd(cmd);
	if (cmd->input != 0)
	{
		dup2(cmd->input, STDIN_FILENO);
		close(cmd->input);
	}
	if (cmd->output != 1)
	{
		dup2(cmd->output, STDOUT_FILENO);
		close(cmd->output);
	}
}
