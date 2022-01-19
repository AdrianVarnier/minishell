/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 16:15:26 by avarnier          #+#    #+#             */
/*   Updated: 2022/01/19 19:01:54 by avarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exec_cd(t_cmd *cmd, t_env *env)
{
	int	ret;

	if (ft_strcmp(cmd->args[1], "-") == 0)
		ret = ft_cd_oldpwd(env);
	else if (ft_strcmp(cmd->args[1], "..") == 0)
		ret = ft_cd_back(env);
	else if (ft_strcmp(cmd->args[1], ".") == 0)
		ret = ft_cd_here(env);
	else if (cmd->args[1] == NULL)
		ret = ft_cd_home(env);
	else
		ret = ft_cd(cmd->args[1], &env);
	return (ret);
}

static int	exec_echo(t_cmd *cmd)
{
	int	ret;

	if (ft_strcmp(cmd->args[1], "-n") == 0)
		ret = ft_echo(cmd->args, 1);
	else
		ret = ft_echo(cmd->args, 0);
	return (ret);
}

void	exec_builtin(t_cmd *cmd, t_env *env, t_file *infile, t_file *outfile)
{
	int		ret;
	char	*err_msg;

	if (ft_strcmp(cmd->args[0], "echo") == 0)
		ret = exec_echo(cmd);
	if (ft_strcmp(cmd->args[0], "cd") == 0)
		ret = exec_cd(cmd, env);
	if (ft_strcmp(cmd->args[0], "pwd") == 0)
		ret = ft_pwd();
	if (ft_strcmp(cmd->args[0], "export") == 0)
		ret = ft_export(cmd->args, &env);
	if (ft_strcmp(cmd->args[0], "unset") == 0)
		ret = ft_unset(cmd->args, &env);
	if (ft_strcmp(cmd->args[0], "env") == 0)
		ret = ft_env(env);
	if (ft_strcmp(cmd->args[0], "exit") == 0)
		ret = ft_exit(cmd, env);
	if (outfile != NULL)
		while (outfile->next != NULL)
			outfile = outfile->next;
	if (outfile != NULL)
	{
		if (outfile->type == PIPE)
		{
			free_shell(env, cmd);
			exit(ret);
		}
	}
	 if (infile != NULL)
	{
		if (infile->type == PIPE)
		{
			free_shell(env, cmd);
			exit(ret);
		}
	}	
	if (is_in_env("?", env) == 1)
		set_env("?", ft_itoa(ret), env);
	else
		add_to_env("?", ft_itoa(ret), &env);
}
