/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 15:48:49 by avarnier          #+#    #+#             */
/*   Updated: 2021/12/17 22:40:51 by avarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_pipe(t_cmd *cmd, t_env *env)
{
	int	fd[2];

	if (pipe(fd) == -1)
	{
		ft_putendl_fd("minishell: pipe failed", 2);
		return ;
	}
	cmd->output = fd[1];
	cmd->next->input = fd[0];
}
