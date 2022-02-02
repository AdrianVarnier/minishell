/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_back.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ali <ali@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 10:59:23 by ali               #+#    #+#             */
/*   Updated: 2022/01/28 18:42:55 by ali              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_handler_quit(int sig)
{
	if (sig == SIGQUIT && g_exit >= 0)
		write(1, "\b\b  \b\b", 6);
	else if (sig == SIGQUIT && g_exit < 0)
		return ;
}

void	ft_handler_int(int sig)
{
	if (sig == SIGINT && g_exit >= 0)
	{
		rl_replace_line("", 1);
		write(1, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
		g_exit = 130;
	}
	else if (sig == SIGINT && g_exit < 0)
	{
		rl_replace_line("", 1);
		write(1, "\n", 1);
		rl_on_new_line();
		g_exit = 130;
	}
}

void	ft_handler_child(int sig)
{
	if (sig == SIGQUIT)
		exit(131);
	else if (sig == SIGINT)
		exit(130);
}

void	ft_handler_heredoc(int sig)
{
	if (sig == SIGQUIT)
		write(1, "\b\b  \b\b", 6);
	if (sig == SIGINT)
		exit(130);
}

void	ft_signal(int mode)
{
	if (mode == 1)
	{
		signal(SIGINT, ft_handler_int);
		signal(SIGQUIT, ft_handler_quit);
		signal(SIGUSR1, ft_handler_child_error);
		signal(SIGILL, ft_handler_child_error);
		signal(SIGUSR2, ft_handler_child_error);
	}
	if (mode == 2)
	{
		signal(SIGINT, ft_handler_child);
		signal(SIGQUIT, ft_handler_child);
	}
	if (mode == 3)
	{
		signal(SIGINT, ft_handler_heredoc);
		signal(SIGQUIT, ft_handler_heredoc);
	}
}
