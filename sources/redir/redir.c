/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@stduent.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 14:15:20 by avarnier          #+#    #+#             */
/*   Updated: 2021/12/17 23:44:59 by avarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <fcntl.h>

void	redir(t_cmd *cmd)
{
	if (cmd->input_type == PIPE)
		close(cmd->prev->output);
	if (cmd->output_type == PIPE)
		close(cmd->next->input);
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
