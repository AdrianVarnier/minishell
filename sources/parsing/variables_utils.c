/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ali <ali@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 13:35:01 by ali               #+#    #+#             */
/*   Updated: 2021/12/14 14:41:24 by ali              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1 && !s2)
		return (0);
	if (!s1)
		return (-1);
	if (!s2)
		return (1);
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

char	*ft_get_varname(char *str)
{
	char	*varname;
	int		i;

	if (*str == '{')
		str++;
	i = 0;
	while (str[i] && str[i] != '}' && str[i] != ' ')
		i++;
	varname = malloc(sizeof(char) * (i + 1));
	if (!varname)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '}' && str[i] != ' ')
	{
		varname[i] = str[i];
		i++;
	}
	varname[i] = '\0';
	return (varname);
}

char	*ft_get_var(char *str, t_env **env)
{
	char	*varname;
	char	*value;

	varname = ft_get_varname(str + 1);
	if (!varname)
		return (NULL);
	value = get_env(varname, *env);
	free(varname);
	return (value);
}

int	ft_variable_size(char *str, t_env **env)
{
	char	*var;
	int		i;
	
	var = ft_get_var(str, env);
	i = 0;
	if (!var)
		return (i);
	while (var[i])
		i++;
	return (i);
}

int	ft_pass_variable(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != ' ' && str[i] != '}')
		i++;
	return (i);
}
