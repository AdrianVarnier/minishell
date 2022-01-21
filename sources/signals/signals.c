/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ali <ali@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 10:59:23 by ali               #+#    #+#             */
/*   Updated: 2022/01/21 01:54:02 by ali              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_handler(int sig)
{
	if (sig == SIGQUIT && g_line == 1)
	{
		g_exit = 131;
		write(1, "Quit (core dumped)", 18);
		rl_replace_line("", 1);
		write(1, "\n", 1);
		rl_on_new_line();
		g_line = 0;
	}
	else if (sig == SIGQUIT && g_line == 0)
	{
		rl_on_new_line();
		rl_redisplay();
		write(1, "  \b\b", 4);
	}
	else if (sig == SIGINT)
	{
		g_exit = 130;
		rl_replace_line("", 1);
		write(1, "\n", 1);
		rl_on_new_line();
		if (g_line == 0)
			rl_redisplay();
		if (g_line == 1)
			g_line = 0;
	}
}

void	ft_signal(void)
{
		signal(SIGINT, ft_handler);
		signal(SIGQUIT, ft_handler);
}
