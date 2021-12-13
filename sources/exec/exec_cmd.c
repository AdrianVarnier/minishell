/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@stduent.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 10:54:07 by avarnier          #+#    #+#             */
/*   Updated: 2021/12/13 18:19:34 by avarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	send_err_msg(char *name, char *full_path, char **path, char mode)
{
	int	i;
	char	*err_msg;

	i = 0;
	while (path[i] != NULL)
	{
		free(path[i]);
		i++;
	}
	free(path);
	free(full_path);
	if (mode == 'F')
	{
		err_msg = ft_strjoin3("minishell: ", name, ": command not found");
		ft_putendl_fd(err_msg, 2);
		free(err_msg);
	}
	if (mode == 'X')
	{
		err_msg = ft_strjoin3("minishell: ", name, ": permission denied");
		ft_putendl_fd(err_msg, 2);
		free(err_msg);
	}
}

static char	*check_path(char **path, t_cmd *cmd)
{
	int	i;
	char	*full_path;

	i = 0;
	while (path[i] != NULL)
	{
		full_path = ft_strjoin3(path[i], "/", cmd->name);
		if (access(full_path, F_OK) == 0)
		{
			if(access(full_path, X_OK) != 0)
			{
				send_err_msg(cmd->name, full_path, path, 'X');
				return (NULL);
			}
			return (full_path);
		}
		free(full_path);
		i++;
	}
	send_err_msg(cmd->name, full_path, path, 'F');
	return (NULL);
}

void	exec_cmd(t_cmd *cmd, t_env *env, t_shell *shell)
{
	char	*tmp;
	char	**path;
	char	**arg;

	redir_pipe(cmd);
	if (is_builtin(cmd->name) == 1)
		exec_builtin(cmd, env, shell);
	tmp = get_env("PATH", env);
	if (tmp == NULL)
	{
		tmp = ft_strjoin3("minishell: ", cmd->name, ": PATH not set");
		ft_putstr_fd(tmp, 2);
		free(tmp);
		free_shell(shell);
		exit(1);
	}
	path = ft_split(tmp, ':');
	tmp = check_path(path, cmd);
	if (tmp != NULL)
	{
		free_char2(path);
		path = env_to_char2(env);
		arg = cmd_to_char2(cmd);
		free_shell(shell);
		execve(tmp, arg, path);
	}
	send_err_msg(NULL, tmp, path, '\0');
	free_shell(shell);
	exit(1);
}
