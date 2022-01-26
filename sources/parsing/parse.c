/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ali <ali@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 17:41:58 by ali               #+#    #+#             */
/*   Updated: 2022/01/26 23:02:24 by ali              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


char	*ft_unquoted_var(char *str, t_env **env)
{
	int		i;
	char	c;

	i = 0;
	c = '\0';
	while (str[i])
	{
		if (str[i] =='\'' || str[i] == '\"')
		{
			c = str[i];
			i++;
			while (str[i] && str[i] != c)
				i++;
		}
		if (str[i] && str[i] == c)
			i++;
		if (ft_is_variable(&str[i]))
			str = ft_replace(str, env);
		if (str[i])
			i++;
	}
	return (str);
}

t_cmd	*ft_exit_parse(char **strs)
{
	free(strs);
	return (NULL);
}

t_cmd	*ft_parse_line(char *line, t_env **env)
{
	char	**strs;
	t_cmd	*cmd;
	char	*exit;

	cmd = NULL;
	exit = ft_itoa(g_exit);
	set_env("?", exit, *env);
	free(exit);
	line = ft_unquoted_var(line, env);
	strs = ft_splitline(line);
	free(line);
	if (ft_parse_error(strs))
		return (ft_exit_parse(strs));
	ft_variables(strs, env);
	ft_quotes(strs);
	cmd = ft_stock_cmd(strs);
	free_char2(strs);
	return (cmd);
}
