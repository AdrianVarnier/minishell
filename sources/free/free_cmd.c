/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 12:30:22 by avarnier          #+#    #+#             */
/*   Updated: 2021/12/11 12:48:02 by avarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_cmd(t_cmd	*cmd)
{
	t_cmd	*tmp;

	while (cmd != NULL)
	{
		tmp = cmd->next;
		if (cmd->name != NULL)
			free(cmd->name);
		if (cmd->option != NULL)
			free(cmd->option);
		if (cmd->arg != NULL)
			free(cmd->arg);
		free(cmd);
		cmd = tmp;
	}
}
