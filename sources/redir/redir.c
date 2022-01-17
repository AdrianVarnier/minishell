/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@stduent.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 14:15:20 by avarnier          #+#    #+#             */
/*   Updated: 2022/01/17 16:57:52 by avarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redir(t_cmd *cmd, t_file *infile, t_file *outfile)
{
	if (infile != NULL)
	{
		while (infile->next != NULL)
			infile = infile->next;
		if (infile->type == PIPE)
			close(cmd->prev->output);
	}
	if (outfile != NULL)
	{
		while (outfile->next != NULL)
			outfile = outfile->next;
		if (outfile->type == PIPE)
			close(cmd->next->input);
	}
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
