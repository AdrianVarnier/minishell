/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@stduent.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 09:05:24 by avarnier          #+#    #+#             */
/*   Updated: 2022/01/13 17:54:27 by avarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(char **arg, int mode)
{
	int	i;

	i = 1;
	if (mode == 1)
		i = 2;
	while (arg[i] != NULL)
	{
		ft_putstr_fd(arg[i], 1);
		if (arg[i + 1] != NULL)
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (mode == 0)
		ft_putchar_fd('\n', 1);
	return (0);
}
