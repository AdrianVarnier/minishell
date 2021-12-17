/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_all_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@stduent.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 22:16:04 by avarnier          #+#    #+#             */
/*   Updated: 2021/12/18 00:28:27 by avarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_all_cmd(t_cmd *cmd, t_env *env)
{
	int		status;
	pid_t	pid;

	if (check_file(cmd) == 0)
		return ;
	while (cmd != NULL)
	{
		if (cmd->output_type == PIPE)
			create_pipe(cmd, env);
		if (is_builtin(cmd->args[0]) == 1 && cmd->output_type != PIPE)
			exec_builtin(cmd, env);
		else
		{
			pid = fork();
			if (pid == 0)
				exec_cmd(cmd, env);
		}
		waitpid(pid, &status, 0);
		if (cmd->input_type == PIPE)
		{
			close(cmd->input);
			close(cmd->prev->output);
		}
		cmd = cmd->next;
	}
}
