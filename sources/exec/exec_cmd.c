/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@stduent.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 18:48:19 by avarnier          #+#    #+#             */
/*   Updated: 2022/02/02 21:41:26 by avarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*send_err_msg(char *name, char mode, pid_t parent, pid_t pid)
{
	char	*err_msg;

	if (pid != 0)
		return (NULL);
	if (mode == 'X')
		kill(parent, SIGUSR1);
	else
		kill(parent, SIGILL);
	if (mode == 'C')
		err_msg = ft_strjoin3("minishell: ", name, ": command not found");
	if (mode == 'F')
		err_msg = ft_strjoin3("minishell: ", name,
				": No such file or directory");
	if (mode == 'X')
		err_msg = ft_strjoin3("minishell: ", name, ": permission denied");
	if (mode == 'P')
		err_msg = ft_strjoin3("minishell: ", name, ": PATH not set");
	if (mode == 'D')
		err_msg = ft_strjoin3("minishell: ", name, ": is a directory");
	if (err_msg != NULL)
	{
		ft_putendl_fd(err_msg, 2);
		free(err_msg);
	}
	return (NULL);
}

static int	is_path(t_cmd *cmd, t_env **env)
{
	int	i;
	int	c;

	if (!cmd->args[0])
		return (0);
	i = 0;
	c = 0;
	while (cmd->args[0][i] != '\0')
	{
		if (cmd->args[0][i] == '/')
			return (1);
		if (cmd->args[0][i] == '.')
			c++;
		i++;
	}
	if (ft_strlen(cmd->args[0]) == c)
	{
		send_err_msg(cmd->args[0], 'C', cmd->parent, cmd->pid);
		exit_wrong_path(cmd, env, 127);
	}
	return (0);
}

static int	check_path(char *name, char *path, pid_t parent, pid_t pid)
{
	if (path == NULL)
		return (0);
	if (access(path, F_OK) != 0)
	{
		if (name == NULL)
			send_err_msg(path, 'F', parent, pid);
		return (0);
	}
	if (access(path, X_OK) != 0)
	{
		if (name == NULL)
			send_err_msg(path, 'X', parent, pid);
		else
			send_err_msg(name, 'X', parent, pid);
		return (-1);
	}
	if (is_dir(path) == 1)
	{
		if (name == NULL)
			send_err_msg(path, 'D', parent, pid);
		else
			send_err_msg(name, 'D', parent, pid);
		return (-1);
	}
	return (1);
}

char	*get_path(t_cmd *cmd, char **path)
{
	int		i;
	char	*full_path;

	i = 0;
	if (path == NULL)
		return (send_err_msg(cmd->args[0], 'P', cmd->parent, cmd->pid));
	if (ft_strcmp(cmd->args[0], "\0") == 0)
		return (send_err_msg(NULL, 'C', cmd->parent, cmd->pid));
	while (path[i] != NULL)
	{
		full_path = ft_strjoin3(path[i++], "/", cmd->args[0]);
		if (check_path(cmd->args[0], full_path, cmd->parent, cmd->pid) == -1)
		{
			free(full_path);
			return (NULL);
		}
		if (check_path(cmd->args[0], full_path, cmd->parent, cmd->pid) == 1)
			return (full_path);
		free(full_path);
	}
	return (send_err_msg(cmd->args[0], 'C', cmd->parent, cmd->pid));
}

void	exec_cmd(t_cmd *cmd, t_env **env)
{
	char	*tmp;
	char	**path;

	path = ft_split(get_env("PATH", *env), ':');
	tmp = NULL;
	ft_signal(2);
	redir(cmd);
	if (is_builtin(cmd->args[0]) == 1)
	{
		free_char2(path);
		exec_builtin(cmd, env, cmd->outfile);
	}
	if (is_path(cmd, env) == 1)
	{
		if (check_path(NULL, cmd->args[0], cmd->parent, cmd->pid) == 1)
			tmp = ft_strdup(cmd->args[0]);
		else
			exit_wrong_path(cmd, env, 0);
	}
	else
		tmp = get_path(cmd, path);
	free_char2(path);
	exec_path(tmp, cmd, *env);
}
