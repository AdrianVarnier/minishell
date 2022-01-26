/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_all_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@stduent.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 22:16:04 by avarnier          #+#    #+#             */
/*   Updated: 2022/01/26 02:21:59 by avarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_all_cmd(t_cmd *cmd, t_env *env)
{
	int		exit_status;

	if (check_file(cmd) == 0)
		return ;
	while (cmd != NULL)
	{
		if (cmd->next != NULL)
			create_pipe(cmd);
		if (is_builtin(cmd->args[0]) == 1 && cmd->next == NULL && cmd->prev == NULL)
			exec_builtin(cmd, env, cmd->infile, cmd->outfile);
		else
		{
			cmd->pid = fork();
			if (cmd->pid == 0)
				exec_cmd(cmd, env);
		}
		if (cmd->prev != NULL)
		{
			close(cmd->pipe_input);
			close(cmd->prev->pipe_output);
		}
		cmd = cmd->next;
	}
	while (waitpid(-1, &exit_status, 0) > 0);
	if (g_exit != 130 && g_exit != 131)
		g_exit = exit_status >> 8;
}
