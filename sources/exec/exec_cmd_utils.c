/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 18:05:48 by avarnier          #+#    #+#             */
/*   Updated: 2022/02/03 11:04:12 by ali              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	close_fd(void)
{
	close(0);
	close(1);
	close(2);
}

int	is_dir(char *path)
{
	DIR	*dir;

	dir = opendir(path);
	if (dir != NULL)
	{
		closedir(dir);
		return (1);
	}
	return (0);
}

void	exit_wrong_path(t_cmd *cmd, t_env **env, int status)
{
	int	exit_status;

	exit_status = 1;
	if (status == 127 || access(cmd->args[0], F_OK) != 0)
		exit_status = 127;
	else if (status == 2)
		exit_status = 2;
	else if (is_dir(cmd->args[0]) == 1 || 
		(access(cmd->args[0], F_OK) == 0 && access(cmd->args[0], X_OK) != 0))
		exit_status = 126;
	free_shell(*env, cmd);
	exit(exit_status);
}

void	exec_path(char *tmp, t_cmd *cmd, t_env *env)
{
	char	**args_tmp;
	char	**env_tmp;

	if (tmp == NULL)
	{
		free_shell(env, cmd);
		exit(127);
	}
	else
	{
		env_tmp = env_to_char2(env);
		args_tmp = char2_dup(cmd->args);
		free_shell_execve(env, cmd);
		if (execve(tmp, args_tmp, env_tmp) == -1)
		{
			free(tmp);
			free_char2(args_tmp);
			free_char2(env_tmp);
			close_fd();
			exit(1);
		}
	}
}
