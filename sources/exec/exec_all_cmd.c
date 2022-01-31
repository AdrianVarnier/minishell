/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_all_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@stduent.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 22:16:04 by avarnier          #+#    #+#             */
/*   Updated: 2022/01/31 04:10:45 by avarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	manage_cmd(t_cmd *cmd, t_env **env, int *builtin)
{
	if (is_builtin(cmd->args[0]) == 1
		&& cmd->next == NULL && cmd->prev == NULL)
	{
		if (cmd->outfile != NULL)
			exec_builtin_redir(cmd, env);
		else
			exec_builtin(cmd, env, cmd->outfile);
		*builtin = 1;
	}
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

void	ft_exit_status(int exit_status, int builtin)
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
	else if (builtin == 0)
		g_exit = exit_status >> 8;
}

void	exec_all_cmd(t_cmd *cmd, t_env **env)
{
	int		exit_status;
	int		builtin;

	exit_status = 0;
	builtin = 0;
	while (cmd != NULL)
	{
		cmd->parent = getpid();
		create_pipe(cmd);
		if (check_file(cmd->infile, cmd->outfile, cmd) == 1)
		{
			g_exit = -1;
			manage_cmd(cmd, env, &builtin);
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
	ft_exit_status(exit_status, builtin);
}
