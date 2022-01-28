/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ali <ali@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 09:17:52 by ali               #+#    #+#             */
/*   Updated: 2022/01/28 18:02:21 by ali              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_handler_child_error(int sig)
{
	printf("CATCHED!");
	if (sig == SIGILL)
		g_exit = -2;
	if (sig == SIGUSR1)
		g_exit = -4;
	if (sig == SIGUSR2)
		g_exit = -3;
}
