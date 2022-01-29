/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 00:07:58 by avarnier          #+#    #+#             */
/*   Updated: 2022/01/30 00:38:34 by avarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo_redir(char **arg, int output, int mode)
{
	int	i;

	i = 1;
	if (mode == 1)
		i = 2;
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
