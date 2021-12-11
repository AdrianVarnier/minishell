/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@stduent.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 18:12:10 by avarnier          #+#    #+#             */
/*   Updated: 2021/12/11 23:55:50 by avarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_equal(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

static char	*get_key(char *s)
{
	int	i;
	char	*key;

	i = 0;
	while (s[i] != '=')
		i++;
	key = (char *)malloc(sizeof(char) * (i + 1));
	i = 0;
	while (s[i] != '=')
	{
		key[i] = s[i];
		i++;
	}
	key[i] = '\0';
	return (key);
}

static char	*get_value(char *s)
{
	int	i;
	int	j;
	char	*value;

	i = 0;
	j = 0;
	while (s[i] != '=')
		i++;
	while (s[j] != '\0')
		j++;
	value = (char *)malloc(sizeof(char) * (j - i + 1));
	i++;
	j = 0;
	while (s[i] != '\0')
	{
		value[j] = s[i];
		i++;
		j++;
	}
	value[j] = '\0';
	return (value);
}

void	ft_export(char *s, t_env **env)
{
	char	*key;
	char	*value;

	if (check_equal(s) == 0)
		return ;
	key = get_key(s);
	value = get_value(s);
	if (is_in_env(key, *env) == 0)
		add_to_env(key, value, env);
	else
		set_env(key, value, *env);
	free(key);
	free(value);
}
