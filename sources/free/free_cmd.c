/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 12:30:22 by avarnier          #+#    #+#             */
/*   Updated: 2021/12/16 16:32:49 by avarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_cmd(t_cmd	*cmd)
{
	t_cmd	*tmp;

	while (cmd->prev != NULL)
		cmd = cmd->prev;
	while (cmd != NULL)
	{
		tmp = cmd->next;
		if (cmd->args != NULL)
			free_char2(cmd->args);
		if (cmd->infile != NULL)
			free(cmd->infile);
		if (cmd->outfile != NULL)
			free(cmd->outfile);
		free(cmd);
		cmd = tmp;
	}
}
