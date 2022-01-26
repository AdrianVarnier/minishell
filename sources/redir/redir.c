/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@stduent.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 14:15:20 by avarnier          #+#    #+#             */
/*   Updated: 2022/01/26 15:45:20 by ali              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redir(t_cmd *cmd)
{
	if (cmd->prev != NULL)
		close(cmd->prev->pipe_output);
	if (cmd->next != NULL)
		close(cmd->next->pipe_input);
	if (cmd->infile != NULL)
		if (cmd->infile->type != PIPE && cmd->prev != NULL)
			close(cmd->pipe_input);
	if (cmd->outfile != NULL)
		if (cmd->outfile->type != PIPE && cmd->next != NULL)
			close(cmd->pipe_output);
	if (cmd->infile != NULL)
	{
		if (cmd->infile->type == PIPE)
		{
			dup2(cmd->pipe_input, STDIN_FILENO);
			close(cmd->pipe_input);
		}
		else if (cmd->input != 0)
		{
			dup2(cmd->input, STDIN_FILENO);
			close(cmd->input);
		}
	}
	else if (cmd->input != 0)
	{
		dup2(cmd->input, STDOUT_FILENO);
		close(cmd->input);
	}
	if (cmd->outfile != NULL)
	{
		if (cmd->outfile->type == PIPE)
		{
			dup2(cmd->pipe_output, STDOUT_FILENO);
			close(cmd->pipe_output);
		}
		else if (cmd->output != 1)
		{
			dup2(cmd->output, STDOUT_FILENO);
			close(cmd->output);
		}
	}
	else if (cmd->output != 1)
	{
		dup2(cmd->output, STDOUT_FILENO);
		close(cmd->output);
	}
}
