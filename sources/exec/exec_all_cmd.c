/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_all_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@stduent.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 22:16:04 by avarnier          #+#    #+#             */
/*   Updated: 2022/01/28 15:34:05 by ali              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	manage_cmd(t_cmd *cmd, t_env *env)
{
	pid_t	parent;

	parent = getpid();
	cmd->parent = parent;
	if (is_builtin(cmd->args[0]) == 1
		&& cmd->next == NULL && cmd->prev == NULL)
		exec_builtin(cmd, env, cmd->outfile);
	else
	{
		cmd->pid = fork();
		if (cmd->pid == 0)
		{
			ft_signal(3);
			exec_cmd(cmd, env);
		}
	}
}

void	ft_exit_status(int exit_status)
{
	if (exit_status == 2)
		g_exit = 130;
	else if (exit_status == 131)
		g_exit = 131;
	else if (g_exit == -2)
		g_exit = 127;
	else if (g_exit == -3)
		g_exit = 1;
	else if (g_exit == -4)
		g_exit = 126;
	else
		g_exit = exit_status >> 8;
}

void	exec_all_cmd(t_cmd *cmd, t_env *env)
{
	int		exit_status;

	exit_status = 0;
	while (cmd != NULL)
	{
		if (cmd->next != NULL)
			create_pipe(cmd);
		if (check_file(cmd->infile, cmd->outfile, cmd) == 1)
		{
			g_exit = -1;
			manage_cmd(cmd, env);
			ft_signal(1);
			if (cmd->prev != NULL)
			{
				close(cmd->pipe_input);
				close(cmd->prev->pipe_output);
			}
		}
		cmd = cmd->next;
	}
	while (waitpid(-1, &exit_status, 0) > 0)
		;
	ft_exit_status(exit_status);
}
