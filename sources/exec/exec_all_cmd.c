/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_all_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@stduent.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 22:16:04 by avarnier          #+#    #+#             */
/*   Updated: 2021/12/17 23:46:36 by avarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_all_cmd(t_cmd *cmd, t_env *env)
{
	pid_t	pid;

	check_file(cmd);
	while (cmd != NULL)
	{
		if (cmd->output_type == PIPE)
			create_pipe(cmd, env);
		pid = fork();
		if (pid == 0)
			exec_cmd(cmd, env);
		if (cmd->input_type == PIPE)
		{
			close(cmd->input);
			close(cmd->prev->output);
		}
		cmd = cmd->next;
	}
}
