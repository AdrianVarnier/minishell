/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ali <ali@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 14:39:31 by ali               #+#    #+#             */
/*   Updated: 2021/12/14 15:58:21 by ali              ###   ########.fr       */
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

void	ft_add_cmd(t_cmd **cmd, char **strs)
{
	int		i;
	t_cmd	*new;

	new = malloc(sizeof(t_cmd));
	if (!new)
		return ;
	i = 0;	
	while (strs[i] && !ft_is_separator(strs[i + 1][0]))
		i++;
	new->args = malloc(sizeof(char *) * (i + 1));
	if (!new->args)
		return ;
	i = 0;
	while (strs[i] && !ft_is_separator(strs[i + 1][0]))
	{
		new->args[i] = strs[i];
		i++;
	}
	new->args[i] = NULL;
	ft_place_cmd(cmd, new);
}

t_cmd	*ft_stock_cmd(char **strs)
{
	int		size;
	int		i;
	int		j;
	t_cmd	*cmd;

	if (strs[0] == NULL)
		return (NULL);
	size = ft_num_cmd(strs);
	i = 0;
	j = 0;
	while (i < size)
	{
		j += ft_next_cmd(&strs[j]);
		ft_add_cmd(&cmd, &strs[j]);
		j += ft_pass_cmd(&strs[j]);
		i++;
	}
	return (cmd);
}
