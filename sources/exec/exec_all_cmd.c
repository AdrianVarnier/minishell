/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_all_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@stduent.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 22:16:04 by avarnier          #+#    #+#             */
/*   Updated: 2022/01/13 18:49:47 by avarnier         ###   ########.fr       */
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

static int	is_pipe(t_file *file)
{
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
		if (is_builtin(cmd->args[0]) == 1 && is_pipe(cmd->outfile) == 0)
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
		if (!(is_builtin(cmd->args[0]) == 1 && is_pipe(cmd->outfile) == 0))
		{
			waitpid(cmd->pid, &exit_status, 0);
			actualise_exit_status(exit_status, env);
		}
		cmd = cmd->next;
	}
}
