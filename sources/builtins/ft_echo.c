/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@stduent.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 09:05:24 by avarnier          #+#    #+#             */
/*   Updated: 2021/12/15 16:15:12 by avarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(char **arg, int mode)
{
	int	i;

	i = 1;
	while (arg[i + 1] != NULL)
	{
		ft_putstr_fd(arg[i], 1);
		ft_putchar_fd(' ', 1);
		i++;
	}
	ft_putstr_fd(arg[i], 1);
	if (mode == 0)
		ft_putchar_fd('\n', 1);
}
