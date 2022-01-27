/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ali <ali@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 10:59:23 by ali               #+#    #+#             */
/*   Updated: 2022/01/27 13:55:09 by ali              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_handler(int sig)
{
	if (sig == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
		write(1, "  \b\b", 4);
	}
	else if (sig == SIGINT)
	{
		rl_replace_line("", 1);
		write(1, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
		g_exit = 130;
	}
}

void	ft_handler2(int sig)
{
	if (sig == SIGQUIT)
	{
		write(1, "Quit (core dumped)", 18);
		rl_replace_line("", 1);
		write(1, "\n", 1);
		rl_on_new_line();
		g_exit = 131;
	}
	else if (sig == SIGINT)
	{
		rl_replace_line("", 1);
		write(1, "\n", 1);
		rl_on_new_line();
		g_exit = 130;
	}
}

void	ft_handler_heredoc(int sig)
{
	if (sig == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
		write(1, "  \b\b", 4);
	}
	if (sig == SIGINT && g_exit == -1)
	{
		g_exit = 130;
		exit(0);
	}
}

void	ft_signal(int mode)
{
	if (mode == 1)
	{
		signal(SIGINT, ft_handler);
		signal(SIGQUIT, ft_handler);
	}
	if (mode == 2)
	{
		signal(SIGINT, ft_handler2);
		signal(SIGQUIT, ft_handler2);
	}
	if (mode == 3)
	{
		signal(SIGINT, ft_handler_heredoc);
		signal(SIGQUIT, ft_handler_heredoc);
	}
}
