/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ali <ali@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 07:45:02 by ali               #+#    #+#             */
/*   Updated: 2022/02/01 08:25:57 by ali              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_prep_heredoc(t_cmd *cmd)
{
	while (cmd != NULL)
	{
		create_all_heredoc(cmd->infile);
		cmd = cmd->next;
	}
}

void	ft_destroy_heredoc(t_cmd *cmd)
{
	int	fd;

	while (cmd != NULL)
	{
		while (cmd->infile)
		{
			if (cmd->infile->type == HEREDOC)
			{
				fd = open(cmd->infile->name, O_RDONLY);
				if (fd != -1)
				{
					close(fd);
					unlink(cmd->infile->name);
				}
			}
			cmd->infile = cmd->infile->next;
		}
		cmd = cmd->next;
	}
}

