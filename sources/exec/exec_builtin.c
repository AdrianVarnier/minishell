/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 16:15:26 by avarnier          #+#    #+#             */
/*   Updated: 2021/12/11 17:05:41 by avarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_cd(t_cmd *cmd, t_env *env)
{
	if (ft_strcmp(cmd->arg, "-") == 0)
		ft_cd_oldpwd(env);
	else if (ft_strcmp(cmd->arg, "..") == 0)
		ft_cd_back(env);
	else if (ft_strcmp(cmd->arg, ".") == 0)
		ft_cd_here(env);
	else if (cmd->arg == NULL)
		ft_cd_home(env);
	else
		ft_cd(cmd->arg, env);
}

static void	exec_echo(t_cmd *cmd)
{
	if (ft_strcmp(cmd->option, "-n") == 0)
		ft_echo(cmd->arg, 1);
	if (cmd->option == NULL)
		ft_echo(cmd->arg, 0);
}

void	exec_builtin(t_cmd *cmd, t_env *env)
{
	if (is_supported(cmd->name, cmd->option) == 0)
	{
		ft_putstr_fd(ft_strjoin5("minishell: ", cmd->name, ": ", 
		cmd->option, ": invalid option\n"), 2);
		return ;
	}
	if (ft_strcmp(cmd->name, "echo") == 0)
		ft_exec_echo(cmd, env);
	if (ft_strcmp(cmd->name, "cd") == 0)
		ft_exec_cd(cmd, env);
	if (ft_strcmp(cmd->name, "pwd") == 0)
		ft_pwd();
	if (ft_strcmp(cmd->name, "export") == 0)
		ft_export(cmd->arg, env);
	if (ft_strcmp(cmd->name, "unset") == 0)
		ft_unset(cmd->arg, env);
	if (ft_strcmp(cmd->name, "env") == 0)
		ft_env(env);
	if (ft_strcmp(cmd->name, "exit") == 0)
		return ;
}
