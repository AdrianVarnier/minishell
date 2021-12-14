/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ali <ali@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 14:39:31 by ali               #+#    #+#             */
/*   Updated: 2021/12/14 19:22:03 by ali              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_add_cmd(t_cmd **cmd, char **strs)
{
	int		i;
	t_cmd	*new;

	new = malloc(sizeof(t_cmd));
	if (!new)
		return ;
	i = 0;	
	while (strs[i] && !ft_is_separator(strs[i][0]))
		i++;
	if (strs[i] && !ft_is_separator(strs[i][0]))
			i++;
	new->args = malloc(sizeof(char *) * (i + 1));
	if (!new->args)
		return ;
	i = 0;
	while (strs[i] && !ft_is_separator(strs[i][0]))
	{
		new->args[i] = strs[i];
		i++;
	}
	new->args[i] = NULL;
	ft_place_cmd(cmd, new);
}

int		ft_next_cmd(char **strs)
{
	int	i;

	i = 0;
	while (strs[i] && strs[i][0] != '|')
	   i++;
	if (!strs[i])
		return (i);
	while (ft_is_separator(strs[i][0]) || ft_is_file(&strs[i], i))
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
		printf("strs[%d] = %s\n", i, strs[i]);
		if (strs[i] && !ft_is_separator(strs[i][0]))
		{
			ft_add_cmd(&cmd, &strs[i]);
			ft_filetype(cmd, &strs[i], i);
		}
		i += ft_next_cmd(&strs[i]);
	}
	return (cmd);
}
