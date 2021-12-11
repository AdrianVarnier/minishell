/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_supported.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@stduent.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 09:17:49 by avarnier          #+#    #+#             */
/*   Updated: 2021/12/11 09:21:18 by avarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_supported(char *name, char *option)
{
	if (option == NULL)
		return (1);
	if (ft_strcmp(name, "echo") == 0)
		if (ft_strcmp(option, "-n") == 0)
			return (1);
	return (0);
}
