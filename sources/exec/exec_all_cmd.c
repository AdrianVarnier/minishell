/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_all_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@stduent.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 22:16:04 by avarnier          #+#    #+#             */
/*   Updated: 2022/01/21 12:53:55 by avarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_pipe(t_file *file)
{
	if (file == NULL)
		return (0);
	while (file->next != NULL)
		file = file->next;
	if (file->type == PIPE)
		return (1);
	else
		return (0);
}

void	exec_all_cmd(t_cmd *cmd, t_env *env)
{
	int		exit_status;

	if (check_file(cmd) == 0)
		return ;
	while (cmd != NULL)
	{
		if (is_pipe(cmd->outfile) == 1)
			create_pipe(cmd);
		if (is_builtin(cmd->args[0]) == 1 && is_pipe(cmd->outfile) == 0 && is_pipe(cmd->infile) == 0)
			exec_builtin(cmd, env, cmd->infile, cmd->outfile);
		else
		{
			cmd->pid = fork();
			if (cmd->pid == 0)
				exec_cmd(cmd, env);
		}
		if (is_pipe(cmd->infile) == 1)
		{
			close(cmd->input);
			close(cmd->prev->output);
		}
		cmd = cmd->next;
	}
	waitpid(-1, &exit_status, 0);
	if (g_exit != 130 && g_exit != 131)
		g_exit = exit_status >> 8;
}
