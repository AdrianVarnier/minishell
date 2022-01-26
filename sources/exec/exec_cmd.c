/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@stduent.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 18:48:19 by avarnier          #+#    #+#             */
/*   Updated: 2022/01/26 15:47:43 by ali              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_path(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] != '\0')
	{
		if (arg[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

static void	send_err_msg(char *name, char mode)
{
	char	*err_msg;

	if (mode == 'C')
		err_msg = ft_strjoin3("minishell: ", name, ": command not found");
	if (mode == 'F')
		err_msg = ft_strjoin3("minishell: ", name,
				": No such file or directory");
	if (mode == 'X')
		err_msg = ft_strjoin3("minishell: ", name, ": permission denied");
	if (mode == 'P')
		err_msg = ft_strjoin3("minishell: ", name, ": PATH not set");
	if (err_msg != NULL)
	{
		ft_putendl_fd(err_msg, 2);
		free(err_msg);
	}
}

static char	check_path(char *name, char *path)
{
	if (path == NULL)
		return (0);
	if (access(path, F_OK) != 0)
	{
		if (name == NULL)
			send_err_msg(path, 'F');
		return (0);
	}
	if (access(path, X_OK) != 0)
	{
		if (name == NULL)
			send_err_msg(path, 'X');
		else
			send_err_msg(name, 'X');
		return (-1);
	}
	return (1);
}

static char	*get_path(t_cmd *cmd, t_env *env)
{
	int		i;
	char	*full_path;
	char	**path;

	i = 0;
	path = ft_split(get_env("PATH", env), ':');
	if (path == NULL)
	{
		send_err_msg(cmd->args[0], 'P');
		return (NULL);
	}
	while (path[i] != NULL)
	{
		full_path = ft_strjoin3(path[i++], "/", cmd->args[0]);
		if (check_path(cmd->args[0], full_path) == -1)
		{
			free(full_path);
			return (NULL);
		}
		if (check_path(cmd->args[0], full_path) == 1)
			return (full_path);
		free(full_path);
	}
	send_err_msg(cmd->args[0], 'C');
	return (NULL);
}

void	exec_cmd(t_cmd *cmd, t_env *env)
{
	char	*tmp;
	char	**env_tmp;
	char	**args_tmp;

	tmp = NULL;
	redir(cmd);
	if (is_builtin(cmd->args[0]) == 1)
	{
		exec_builtin(cmd, env, cmd->outfile);
		free_shell(env, cmd);
		exit(0);
	}
	if (is_path(cmd->args[0]) == 1)
	{
		if (check_path(NULL, cmd->args[0]) == 1)
			tmp = ft_strdup(cmd->args[0]);
	}
	else
		tmp = get_path(cmd, env);
	if (tmp == NULL)
	{
		free_shell(env, cmd);
		exit(1);
	}
	else
	{
		env_tmp = env_to_char2(env);
		args_tmp = char2_dup(cmd->args);
		free_shell(env, cmd);
		if (execve(tmp, args_tmp, env_tmp) == -1)
		{
			free(tmp);
			free_char2(args_tmp);
			free_char2(env_tmp);
			exit(1);
		}
	}
}
