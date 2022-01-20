/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ali <ali@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 10:59:23 by ali               #+#    #+#             */
/*   Updated: 2022/01/20 18:30:10 by ali              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_handler(int sig)
{
	if (sig == SIGINT)
		g_exit = 130;
	if (sig == SIGQUIT)
	{
		g_exit = 131;
		write(1, "Quit (core dumped)", 18);
	}
	rl_replace_line("", 1);
	write(1, "\n", 1);
	rl_on_new_line();
	if (g_line == 0)
		rl_redisplay();
	if (g_line == 1)
		g_line = 0;
}

void	ft_signal(void)
{
		signal(SIGINT, ft_handler);
		signal(SIGQUIT, ft_handler);
}
