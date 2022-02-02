/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 12:16:24 by avarnier          #+#    #+#             */
/*   Updated: 2022/02/02 18:58:53 by avarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_shell(t_env *env, t_cmd *cmd)
{
	close(0);
	close(1);
	close(2);
	free_env(env);
	free_cmd(cmd);
	rl_clear_history();
}
