/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 00:07:58 by avarnier          #+#    #+#             */
/*   Updated: 2022/01/30 01:06:11 by ali              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo_redir(char **arg, int output, int mode)
{
	int	i;

	i = 1;
	while (mode == 1 && arg[i] && is_n(arg[i]))
		i++;
	while (arg[i] != NULL)
	{
		ft_putstr_fd(arg[i], output);
		if (arg[i + 1] != NULL)
			ft_putchar_fd(' ', output);
		i++;
	}
	if (mode == 0)
		ft_putchar_fd('\n', output);
	return (0);
}
