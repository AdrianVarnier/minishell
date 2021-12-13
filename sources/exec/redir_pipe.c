/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 17:37:18 by avarnier          #+#    #+#             */
/*   Updated: 2021/12/13 18:07:54 by avarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdio.h>

void	redir_pipe(t_cmd *cmd)
{
	if (cmd == NULL)
		return ;
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
