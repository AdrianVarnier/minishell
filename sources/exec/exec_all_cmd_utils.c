/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_all_cmd_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ali <ali@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 15:16:50 by ali               #+#    #+#             */
/*   Updated: 2022/02/03 17:13:33 by ali              ###   ########.fr       */
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
	t_file	*infile;
	t_file	*outfile;

	while (cmd)
	{
		infile = cmd->infile;
		while (infile)
		{
			if (infile->fd > 2)
				close(infile->fd);
			infile = infile->next;
		}
		outfile = cmd->outfile;
		while (outfile)
		{
			if (outfile->fd > 2)
				close(outfile->fd);
			outfile = outfile->next;
		}
		cmd = cmd->next;
	}
}
