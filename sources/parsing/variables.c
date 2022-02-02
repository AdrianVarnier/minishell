/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ali <ali@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 16:23:13 by ali               #+#    #+#             */
/*   Updated: 2022/02/02 21:41:27 by ali              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_size_sub(char *str, t_env **env, int nospace)
{
	int	size;
	int	i;

	size = 0;
	i = 0;
	while (str[i])
	{
		if (!ft_is_variable(&str[i]))
		{
			i++;
			size++;
		}
		else
		{
			size += ft_variable_size(&str[i], env, nospace);
			i += ft_pass_variable(&str[i]);
		}
	}
	return (size);
}

int	ft_sub(char *sub, char *str, t_env **env, int nospace)
{
	int		i;
	int		j;
	char	*var;

	i = 0;
	j = 0;
	var = ft_get_var(str, env);
	if (!var)
		return (0);
	while (var[i])
	{
		while (var[i] == ' ' && var[i + 1] && var[i + 1] == ' ' && nospace)
			i++;
		if (var[i])
		{
			sub[j] = var[i];
			i++;
			j++;
		}
	}
	sub[j] = '\0';
	free(var);
	return (i);
}

void	ft_fill_sub(char *str, char *sub, int *size, t_env **env)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (j < size[0])
	{
		if (!ft_is_variable(&str[i]))
		{
			sub[j] = str[i];
			i++;
			j++;
		}
		else
		{
			j += ft_sub(&sub[j], &str[i], env, size[1]);
			i += ft_pass_variable(&str[i]);
		}
	}
	sub[j] = '\0';
}

char	*ft_replace(char *str, t_env **env, int nospace)
{
	char	*sub;
	int		size[2];

	size[0] = ft_size_sub(str, env, nospace);
	size[1] = nospace;
	sub = malloc(sizeof(char) * (size[0] + 1));
	if (!sub)
		return (NULL);
	ft_fill_sub(str, sub, size, env);
	if (str)
		free (str);
	return (sub);
}

void	ft_variables(char **strs, t_env **env)
{
	int	i;
	int	j;
	int	novar;
	int	nospace;

	novar = 0;
	nospace = 1;
	i = -1;
	while (strs[++i])
	{
		j = -1;
		while (strs[i][++j])
		{
			if (strs[i][j] == '\'' && novar == 0)
				novar = 1;
			else if (strs[i][j] == '\'' && novar == 1)
				novar = 0;
			if (strs[i][j] == '\"' && nospace == 1)
				nospace = 0;
			else if (strs[i][j] == '\"' && nospace == 0)
				nospace = 1;
			if (novar == 0 && strs[i][j] && ft_is_variable(&strs[i][j]))
				strs[i] = ft_replace(strs[i], env, nospace);
		}
	}
}
