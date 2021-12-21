/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_all_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@stduent.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 22:16:04 by avarnier          #+#    #+#             */
/*   Updated: 2021/12/21 22:01:59 by avarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	actualise_exit_status(int exit_status, t_env *env)
{
	if (is_in_env("?", env) == 1)
		set_env("?", ft_itoa(exit_status >> 8), env);
	else
		add_to_env("?", ft_itoa(exit_status >> 8), &env);
}

void	exec_all_cmd(t_cmd *cmd, t_env *env)
{
	int		exit_status;

	if (check_file(cmd) == 0)
		return ;
	while (cmd != NULL)
	{
		if (cmd->output_type == PIPE)
			create_pipe(cmd);
		if (is_builtin(cmd->args[0]) == 1 && cmd->output_type != PIPE)
			exec_builtin(cmd, env);
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
		waitpid(cmd->pid, &exit_status, 0);
		actualise_exit_status(exit_status, env);
		cmd = cmd->next;
	}
}
