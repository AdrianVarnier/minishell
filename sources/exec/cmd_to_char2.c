/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_to_char2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 11:47:54 by avarnier          #+#    #+#             */
/*   Updated: 2021/12/13 12:50:25 by avarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	cmd_size(t_cmd *cmd)
{
	int	i;

	i = 0;
	if (cmd->name != NULL)
		i++;
	if (cmd->option != NULL)
		i++;
	if (cmd->arg != NULL)
		i++;
	return (i);
}

char	**cmd_to_char2(t_cmd *cmd)
{
	int	i;
	char	**ret;

	if (cmd == NULL)
		return (NULL);
	i = 0;
	ret = (char **)malloc(sizeof(char *) * (cmd_size(cmd) + 1));
	if (cmd->name != NULL)
	{
		ret[i] = ft_strdup(cmd->name);
		i++;
	}
	if (cmd->option != NULL)
	{
		ret[i] = ft_strdup(cmd->option);
		i++;
	}
	if (cmd->arg != NULL)
	{
		ret[i] = ft_strdup(cmd->arg);
		i++;
	}
	ret[i] = NULL;
	return (ret);
}
