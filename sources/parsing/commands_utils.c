/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ali <ali@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 14:03:09 by ali               #+#    #+#             */
/*   Updated: 2021/12/14 15:59:08 by ali              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_file(char **strs, int index)
{
	if (index == 0)
		return (0);
	if (strs[-1][0] == '<' || strs[-1][0] == '>')
		return (1);
	return (0);
}

void	ft_place_cmd(t_cmd **cmd, t_cmd *new)
{
	t_cmd	*index;

	if (*cmd == NULL)
	{
		new->next = NULL;
		new->prev = NULL;
		*cmd = new;
	}
	else
	{
		index = *cmd;
		while (index->next != NULL)
			index = index->next;
		new->next = NULL;
		index->next = new;
	}
}
