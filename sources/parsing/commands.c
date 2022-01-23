/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ali <ali@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 14:39:31 by ali               #+#    #+#             */
/*   Updated: 2022/01/23 15:35:48 by ali              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_count_args(char **strs)
{
	int	i;
	int	args_nb;

	i = 0;
	args_nb = 0;
	while (strs[i] && strs[i][0] != '|')
	{
		if (!ft_is_separator(strs[i][0]) && !ft_is_file(&strs[i], i))
			args_nb++;
		i++;
	}
	return (args_nb);
}

void	ft_fill_args(char **strs, char **args)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (strs[i] && strs[i][0] != '|')
	{
		if (!ft_is_separator(strs[i][0]) && !ft_is_file(&strs[i], i))
		{
			args[j] = ft_strdup(strs[i]);
			j++;
		}
		i++;
	}
}

void	ft_add_cmd(t_cmd **cmd, char **strs)
{
	t_cmd	*new;
	int		args_nb;

	new = malloc(sizeof(t_cmd));
	if (!new)
		return ;
	args_nb = ft_count_args(strs);
	new->args = malloc(sizeof(char *) * (args_nb + 1));
	if (!new->args)
		return ;
	ft_fill_args(strs, new->args);
	new->args[args_nb] = NULL;
	new->input = 0;
	new->output = 1;
	ft_place_cmd(cmd, new);
}

int	ft_next_cmd(char **strs)
{
	int	i;

	i = 0;
	if (strs[i][0] == '<')
	{
		while (strs[i] && (ft_is_file(&strs[i], i)
				|| ft_is_separator(strs[i][0])))
			i++;
		return (i);
	}
	while (strs[i] && strs[i][0] != '|')
		i++;
	if (!strs[i])
		return (i);
	while (strs[i] && (ft_is_separator(strs[i][0]) || ft_is_file(&strs[i], i)))
		i++;
	return (i);
}

t_cmd	*ft_stock_cmd(char **strs)
{
	t_cmd	*cmd;
	int		i;

	if (strs[0] == NULL)
		return (NULL);
	cmd = NULL;
	i = 0;
	while (strs[i])
	{
		if (strs[i] && !ft_is_separator(strs[i][0]))
		{
			ft_add_cmd(&cmd, &strs[i]);
			ft_filetype(cmd, &strs[i], i);
		}
		i += ft_next_cmd(&strs[i]);
	}
	return (cmd);
}
