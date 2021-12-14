/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ali <ali@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 14:39:31 by ali               #+#    #+#             */
/*   Updated: 2021/12/13 14:10:56 by ali              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_num_cmd(char **strs)
{
	int	cmd;
	int	i;

	cmd = 0;
	i = 0;
	while (strs[i])
	{
		if (!ft_is_separator(strs[i][0]) && !ft_is_file(&strs[i], i))
		{
			cmd++;
			while (strs[i] && !ft_is_separator(strs[i][0]))
				i++;
		}
		if (strs[i])
			i++;
	}
	return (cmd);
}

int	ft_next_cmd(char **strs)
{
	int	i;

	i = 0;
	while (strs[i] && (ft_is_separator(strs[i][0]) || ft_is_file(&strs[i], i)))
		i++;
	return (i);
}

int	ft_pass_cmd(char **strs)
{
	int	i;

	i = 0;
	while (strs[i] && !ft_is_separator(strs[i][0]))
		i++;
	while (strs[i] && (ft_is_separator(strs[i][0]) || ft_is_file(&strs[i], i)))
		i++;
	return (i);
}

void	ft_cpy_cmd(t_command *cmd, char **strs)
{
	int	i;
	int	args;

	cmd->cmd = strs[0];
	args = 0;
	while (strs[args + 1] && !ft_is_separator(strs[args + 1][0]))
		args++;
	cmd->arg = malloc(sizeof(char *) * (args + 1));
	if (!cmd->arg)
		return ;
	i = 1;
	while (strs[i] && !ft_is_separator(strs[i][0]))
	{
		cmd->arg[i - 1] = strs[i];
		i++;
	}
	cmd->arg[i - 1] = NULL;
}

t_command	*ft_stock_cmd(char **strs)
{
	int			size;
	int			i;
	int			j;
	t_command	*cmds;

	if (strs[0] == NULL)
		return (NULL);
	size = ft_num_cmd(strs);
	cmds = malloc(sizeof(t_command) * (size + 1));
	if (!cmds)
		return (NULL);
	i = 0;
	j = 0;
	while (i < size)
	{
		j += ft_next_cmd(&strs[j]);
		ft_cpy_cmd(&cmds[i], &strs[j]);
		if (cmds[i].cmd)
		j += ft_pass_cmd(&strs[j]);
		i++;
	}
	cmds[i].cmd = NULL;
	cmds[i].arg = NULL;
	return (cmds);
}
