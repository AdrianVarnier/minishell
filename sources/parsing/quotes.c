/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ali <ali@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 15:55:05 by ali               #+#    #+#             */
/*   Updated: 2021/12/15 16:16:44 by ali              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_quote_closed(char *str)
{
	int		i;
	char	c;

	c = str[0];
	i = 1;
	while (str[i] && str[i] != c)
		i++;
	if (!str[i])
		return (0);
	return (1);
}

char	*ft_remove_quote(char *str)
{
	char	c;
	char	*sub;
	int		i;

	if (!ft_quote_closed(str))
		return (str);
	c = str[0];
	i = 1;
	while (str[i] != c)
		i++;
	sub = malloc(sizeof(char) * i);
	if (!sub)
		return (NULL);
	i = 0;
	while (str[i + 1] != c)
	{
		sub[i] = str[i + 1];
		i++;
	}
	sub[i] = '\0';
	free(str);
	return (sub);
}
