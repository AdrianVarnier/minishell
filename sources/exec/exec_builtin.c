/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 16:15:26 by avarnier          #+#    #+#             */
/*   Updated: 2021/12/15 21:40:54 by avarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_cd(t_cmd *cmd, t_env *env)
{
	if (ft_strcmp(cmd->args[1], "-") == 0)
		ft_cd_oldpwd(env);
	else if (ft_strcmp(cmd->args[1], "..") == 0)
		ft_cd_back(env);
	else if (ft_strcmp(cmd->args[1], ".") == 0)
		ft_cd_here(env);
	else if (cmd->args[1] == NULL)
		ft_cd_home(env);
	else
		ft_cd(cmd->args[1], &env);
}

static void	exec_echo(t_cmd *cmd)
{
	if (ft_strcmp(cmd->args[1], "-n") == 0)
		ft_echo(cmd->args, 1);
	else
		ft_echo(cmd->args, 0);
}

void	exec_builtin(t_cmd *cmd, t_env *env, t_shell *shell)
{
	char	*err_msg;

	if (ft_strcmp(cmd->args[0], "echo") == 0)
		exec_echo(cmd);
	if (ft_strcmp(cmd->args[0], "cd") == 0)
		exec_cd(cmd, env);
	if (ft_strcmp(cmd->args[0], "pwd") == 0)
		ft_pwd();
	if (ft_strcmp(cmd->args[0], "export") == 0)
		ft_export(cmd->args, &env);
	if (ft_strcmp(cmd->args[0], "unset") == 0)
		ft_unset(cmd->args, env);
	if (ft_strcmp(cmd->args[0], "env") == 0)
		ft_env(env);
	if (ft_strcmp(cmd->args[0], "exit") == 0)
		return ;
	free_shell(shell);
}
