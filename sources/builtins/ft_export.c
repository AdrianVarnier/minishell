/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@stduent.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 18:12:10 by avarnier          #+#    #+#             */
/*   Updated: 2022/01/21 20:07:22 by avarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_invalid(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0' && s[i] != '=')
	{
		if (s[i] == '?')
			return (1);
		i++;
	}
	return (0);
}

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
	int		i;
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
	int		i;
	int		j;
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

int	ft_export(char **arg, t_env **env)
{
	int		i;
	char	*key;
	char	*value;

	i = 1;
	while (arg[i] != NULL)
	{
		if (check_invalid(arg[i]) == 0)
			return (1);
		if (check_equal(arg[i]) == 0)
			return (0);
		key = get_key(arg[i]);
		value = get_value(arg[i]);
		if (is_in_env(key, *env) == 0)
			add_to_env(key, value, env);
		else
			set_env(key, value, *env);
		free(key);
		free(value);
		i++;
	}
	return (0);
}
