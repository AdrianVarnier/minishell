/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 18:05:48 by avarnier          #+#    #+#             */
/*   Updated: 2022/01/29 22:40:56 by avarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_path(char *tmp, t_cmd *cmd, t_env *env)
{
	char	**args_tmp;
	char	**env_tmp;

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
