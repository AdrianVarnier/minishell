/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ali <ali@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 15:55:05 by ali               #+#    #+#             */
/*   Updated: 2022/01/21 16:13:24 by ali              ###   ########.fr       */
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

void	ft_fill_unquote(char *sub, char *str, char c)
{
	int	i;
	int	j;
	
	i = 0;
	j = 0;
	while (str[j])
	{
		while (str[j] && str[j] == c)
			j++;
		while (str[j] && str[j] != c)
		{
			sub[i] = str[j];
			i++;
			j++;
		}
	}
	sub[i] = '\0';
}

int	ft_size_unquote(char *str, int c)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	while (str[i])
	{
		while (str[i] && str[i] == c)
			i++;
		while (str[i] && str[i] != c)
		{
			i++;
			size++;
		}
	}
	return (size);
}

char	*ft_remove_quote(char *str)
{
	char	c;
	char	*sub;
	int		i;
	int		size;

	i = 0;
	while (str[i] && str[i] != '\'' && str[i] != '\"')
		i++;
	if (!str[i])
		return (str);
	if (!ft_quote_closed(&str[i]))
		return (str);
	c = str[i];
	size = ft_size_unquote(str, c);
	sub = malloc(sizeof(char) * (size + 1));
	if (!sub)
		return (NULL);
	ft_fill_unquote(sub, str, c);
	free(str);
	return (ft_remove_quote(sub));
}
