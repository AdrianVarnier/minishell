/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ali <ali@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 18:26:23 by ali               #+#    #+#             */
/*   Updated: 2022/01/27 00:29:34 by ali              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_variable(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '$' && str[i + 1] && (str[i + 1] == '?' || str[i + 1] == '{'))
		return (1);
	if (str[i] == '$' && str[i + 1]
		&& !ft_is_vardel(str[i + 1], " ,.?/][}+=-*%$#@!\'\"\0"))
		return (1);
	return (0);
}

int ft_is_vardel(char c, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}
