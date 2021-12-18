/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_all_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@stduent.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 22:16:04 by avarnier          #+#    #+#             */
/*   Updated: 2021/12/18 05:26:56 by avarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_all_cmd(t_cmd *cmd, t_env *env, int *exit_status)
{
	int		status;

	if (check_file(cmd) == 0)
		return ;
	while (cmd != NULL)
	{
		if (cmd->output_type == PIPE)
			create_pipe(cmd, env);
		if (is_builtin(cmd->args[0]) == 1 && cmd->output_type != PIPE)
			exec_builtin(cmd, env, exit_status);
		else
		{
			cmd->pid = fork();
			if (cmd->pid == 0)
				exec_cmd(cmd, env);
		}
		if (cmd->input_type == PIPE)
		{
			close(cmd->input);
			close(cmd->prev->output);
		}
		waitpid(cmd->pid, exit_status, 0);
		cmd = cmd->next;
	}
}
