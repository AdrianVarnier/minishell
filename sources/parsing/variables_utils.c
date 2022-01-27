/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ali <ali@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 13:35:01 by ali               #+#    #+#             */
/*   Updated: 2022/01/27 20:08:56 by ali              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_varname_exit(void)
{
	char	*varname;

	varname = malloc(sizeof(char) * 2);
	if (!varname)
		return (NULL);
	varname[0] = '?';
	varname[1] = '\0';
	return (varname);
}

char	*ft_get_varname(char *str)
{
	char	*varname;
	int		i;

	if (*str == '{')
		str++;
	if (*str == '?')
		return (ft_varname_exit());
	i = 0;
	while (str[i] && !ft_is_vardel(str[i], " ,.?/][}+=-*%$#@!|><\'\"\0"))
		i++;
	varname = malloc(sizeof(char) * (i + 1));
	if (!varname)
		return (NULL);
	i = 0;
	while (str[i] && !ft_is_vardel(str[i], " ,.?/][}+=-*%$#@!|<>\'\"\0"))
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

	i = 1;
	if (str[i] == '?')
		return (2);
	if (str[i] == '{')
	{
		while (str[i] && str[i] != '}')
			i++;
		if (str[i])
			return (i + 1);
		return (i);
	}
	i++;
	while (str[i] && !ft_is_vardel(str[i], " ,.?/][{}+=-*%$#@!|<>\'\"\0"))
		i++;
	return (i);
}
