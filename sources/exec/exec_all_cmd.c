/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_all_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@stduent.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 22:16:04 by avarnier          #+#    #+#             */
/*   Updated: 2021/12/18 01:37:17 by avarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	cmd_size(t_cmd *cmd)
{
	int	i;

	i = 0;
	if (cmd == NULL)
		return (0);
	while (cmd != NULL)
	{
		if (!(is_builtin(cmd->args[0]) == 1 && cmd->output_type != PIPE))
			i++;
		cmd = cmd->next;
	}
	return (i);
}

void	exec_all_cmd(t_cmd *cmd, t_env *env)
{
	int		i;
	int		status;
	pid_t	pid[cmd_size(cmd)];

	i = 0;
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
			pid[i] = fork();
			if (pid[i] == 0)
				exec_cmd(cmd, env);
			i++;
		}
		if (cmd->input_type == PIPE)
		{
			close(cmd->input);
			close(cmd->prev->output);
		}
		waitpid(pid[i], &status, 0);
		cmd = cmd->next;
	}
}
