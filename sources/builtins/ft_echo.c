/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@stduent.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 09:05:24 by avarnier          #+#    #+#             */
/*   Updated: 2021/12/11 15:24:32 by avarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(char *s, int mode)
{
	ft_putstr_fd(s, 1);
	if (mode == 0)
		ft_putstr_fd("\n", 1);
}
